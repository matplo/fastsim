#!/usr/bin/env python

import os
import sys
import evernote.api.client as enClient
import evernote.edam.notestore as enStore
import evernote.edam.type.ttypes as enTypes
import evernote.edam.error.ttypes as enErrors
import hashlib

from utils import *

from cachepickled import cachepickled as cache

import datetime
    
class ENoterSetup:
    default_dev_token  = 'S=s1:U=904fb:E=152ac1870e0:C=14b54674120:P=1cd:A=en-devtoken:V=2:H=1993fecb1c0c1cf6158801c186d0e51d'
    default_prod_token = 'S=s44:U=4a1a5a:E=152ac4525a7:C=14b5493f670:P=1cd:A=en-devtoken:V=2:H=f76e7e0a01f049e12e9748e82bde0cbe'
    default_c_secret   = '9f451936519fb24e'
    default_c_key      = 'ploskon'
    default_sandbox    = True
    default_use_cache  = True
    default_cache      = './cache/default/'
    
    def __init__(self, **args):        
        self.c_secret  = not_none(self.default_c_secret,  args.get('c_secret'))
        self.c_key     = not_none(self.default_c_key,     args.get('c_key'))
        self.sandbox   = not_none(self.default_sandbox,   args.get('sandbox'))
        self.use_cache = not_none(self.default_use_cache, args.get('use_cache'))
        self.cache     = not_none(self.default_cache,     args.get('cache'))
        self.token     = args.get('token')
        if self.token == None:
            if self.sandbox == True:
                self.token = self.default_dev_token
                self.cache = self.cache + '/dev/'
            else:
                self.token = self.default_prod_token
                self.cache = self.cache + '/prod/'
        self.filter_words       = None
        
    def __repr__(self):
        return '[i] EnoterSetup:\n' + Inspector(self).table_members_basic()

class ENoter:
    def __init__(self, setup):
        self.setup      = setup
        self.reset()
        self.check_cache()
        
    def reset(self):
        self.client     = None
        self.user_store = None
        self.user       = None
        self.note_store = None

    def check_cache(self):
        if os.path.isdir(self.setup.cache):
            pass
        else:
            try:
                os.makedirs(self.setup.cache)
            except OSError as e:
                debug('e','unable to create cache dirs', e)

    def get_client(self):
        debug( )
        if self.client == None:
            try:
                self.client = enClient.EvernoteClient(sandbox=self.setup.sandbox,
                                                      token=self.setup.token,
                                                      consumer_key=self.setup.c_key,
                                                      consumer_secret=self.setup.c_secret)
            except:
                debug('e', 'unable to get_client')
                return None
        debug_obj( self.client )
        return self.client

    def get_user_store(self):
        if self.user_store == None:
            self.user_store = self.get_client().get_user_store()
        debug_obj ( self.user_store )
        return self.user_store

    def get_user(self):
        if self.user != None:
            return self.user
        try:
            self.user = self.get_user_store().getUser()
            debug_obj( self.user )
        except enErrors.EDAMSystemException as edue:
            debug('e','unable to getUser; error is:',edue)
            return None
        return self.user
    
    def get_note_store(self):
        if self.note_store != None:
            return self.note_store
        try:
            self.note_store = self.get_client().get_note_store()
        except enErrors.EDAMUserException as e:
            debug('e', '(UserE) unable to get_note_store; error is:',e)
            return None            
        except enErrors.EDAMSystemException as e:
            debug('e', '(SysE) unable to get_note_store; error is:',e)
            return None            
        except enErrors.EDAMNotFoundException as e:
            debug('e', '(NFound) unable to get_note_store; error is:',e)
            return None            
        except:
            debug('e', '(other) unable to get_note_store')
            return None
        debug_obj ( self.note_store )
        return self.note_store

    def get_notebooks(self):
        cache_name = self.setup.cache + '_notebooks'
        if self.setup.use_cache == False:
            try:
                self.notebooks = self.get_note_store().listNotebooks()
                st = cache.write(cache_name, self.notebooks)
                print '[i] cache & timestamp:',cache_name, st
            except enErrors.EDAMSystemException as edue:
                debug('e','unable to get notebooks; error is:',edue)
                return None
            except:
                debug('e','unable to get notebooks')
                return None                
        else:
            self.notebooks = cache.read(cache_name)            
        #debug_obj(self.notebooks)
        return self.notebooks

    def create_note(self, title, contents):
        noteStore = self.get_note_store()
        if noteStore == None:
            debug('e', 'unable to create a note')
            return
        note = enTypes.Note()
        note.title = title
        note.content = '<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE en-note SYSTEM "http://xml.evernote.com/pub/enml2.dtd">'
        note.content += '<en-note>' + contents + '</en-note>'
        created_note = noteStore.createNote(note)
        print "Successfully created a new note with GUID: ", created_note.guid

    # from: https://dev.evernote.com/doc/articles/creating_notes.php
    def makeNote(authToken, noteStore, noteTitle, noteBody, parentNotebook=None):
 
        nBody = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        nBody += "<!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\">"
        nBody += "<en-note>%s</en-note>" % noteBody
 
        ## Create note object
        ourNote = Types.Note()
        ourNote.title = noteTitle
        ourNote.content = nBody
 
        ## parentNotebook is optional; if omitted, default notebook is used
        if parentNotebook and hasattr(parentNotebook, 'guid'):
            ourNote.notebookGuid = parentNotebook.guid
 
        ## Attempt to create note in Evernote account
        try:
            note = noteStore.createNote(authToken, ourNote)
        except enErrors.EDAMUserException as edue:
            ## Something was wrong with the note data
            ## See EDAMErrorCode enumeration for error code explanation
            ## http://dev.evernote.com/documentation/reference/Errors.html#Enum_EDAMErrorCode
            print "EDAMUserException:", edue
            return None
        except enErrors.EDAMNotFoundException, ednfe:
            ## Parent Notebook GUID doesn't correspond to an actual notebook
            print "EDAMNotFoundException: Invalid parent notebook GUID"
            return None
        ## Return created note object
        return note
    
    def get_note_list(self, nlast = 3):
        flter = enStore.NoteStore.NoteFilter()
        flter.ascending = False
        flter.words = self.setup.filter_words
        debug_obj ( flter )
 
        spec = enStore.NoteStore.NotesMetadataResultSpec()
        spec.includeTitle = True
        spec.includeNotebookGuid = True
        spec.includeCreated = True
        spec.includeUpdated = True
        spec.includeTagGuids = True
        spec.includeAttributes = True        
        debug_obj( spec )

        strflter    = str(flter)
        hash_object = hashlib.md5(strflter.encode())
        hash_hex    = hash_object.hexdigest()
        cache_name  = self.setup.cache + '_noteList_' + hash_hex
        debug( strflter, cache_name )
        
        noteList = None
        if self.setup.use_cache == False: 
            noteStore = self.get_note_store()
            if noteStore == None:
                return
            try:
                noteList = noteStore.findNotesMetadata(flter, 0, nlast, spec)
                st = cache.write(cache_name, noteList)
                print '[i] cache & timestamp:',cache_name, st
            except:
                debug( 'e', 'unable to get the note list')
        else:
            noteList = cache.read(cache_name)
        return noteList

    def get_note(self, guid):
        note = None
        cache_name = self.setup.cache + '_noteList_' + str(guid)
        if self.setup.use_cache == False: 
            noteStore = self.get_note_store()
            if noteStore == None:
                return
            withContent = True
            withResourcesData = True
            withResourcesRecognition = True
            withResourcesAlternateData = True
            try:
                note = noteStore.getNote(guid,
                                         withContent,
                                         withResourcesData,                                         
                                         withResourcesRecognition,
                                         withResourcesAlternateData)
                st = cache.write(cache_name, note)
                print '[i] cache & timestamp:',cache_name, st            
            except enErrors.EDAMUserException as e:
                debug('e', '(UserE) unable to get the note id:', guid, e)
            except enErrors.EDAMSystemException as e:
                debug('e', '(SysE) unable to get the note id:', guid, e)
            except enErrors.EDAMNotFoundException as e:
                debug('e', '(NFound) unable to get the note id:', guid, e)                
            except:
                debug('e', 'unable to get the note id:', guid)
        else:
            note = cache.read(cache_name)
        return note
    
def create_notebook(client, name = 'Dev Notebook'):
    debug()
    noteStore = get_note_store(client)
    if noteStore == None:
        return
    notebook = enTypes.Notebook()
    notebook.name = name
    try:
        notebook = noteStore.createNotebook(notebook)
        debug('new notebook [name guid]',notebook.name,notebook.guid)
    except enErrors.EDAMUserException as edue:
        debug('e','notebook',name,'unable to create error is:',edue)
    except enErrors.EDAMSystemException as edue:
        debug('e','notebook',name,'unable to create error is:',edue)
    
dev_token='S=s1:U=904fb:E=152ac1870e0:C=14b54674120:P=1cd:A=en-devtoken:V=2:H=1993fecb1c0c1cf6158801c186d0e51d'
prod_token='S=s44:U=4a1a5a:E=152ac4525a7:C=14b5493f670:P=1cd:A=en-devtoken:V=2:H=f76e7e0a01f049e12e9748e82bde0cbe'

def test():
    token = dev_token
    if '--prod' in sys.argv:
        token = prod_token
    sandbox = True
    if token == dev_token:
        sandbox = True
    if token == prod_token:
        sandbox = False
    debug('sandbox:',sandbox)
    
    client = get_client(token, sandbox=sandbox)
    test_auth(client)
    print_notebooks(client)
    create_notebook(client)
    print_notebooks(client)
    get_linked_notebooks(client, token)

def test1():
    sandbox = True
    if '--prod' in sys.argv:
        sandbox = False
    if '--no-cache' in sys.argv:
        use_cache = False
    else:
        use_cache = True
    setup = ENoterSetup(sandbox=sandbox,use_cache=use_cache)
    #print Inspector(setup).table_members_all()
    debug ( setup )
    enoter = ENoter(setup)
    enoter.get_client()
    enoter.get_user()
    notebooks = enoter.get_notebooks()
    if '--create-test-note' in sys.argv:
        enoter.create_note('test note at:' + str(datetime.datetime.now()), '<div> content from </div> </br> <div> python... </div>')
    enoter.read_notes()
    debug ('.')

def usage():
    print '[i]',os.path.basename(sys.argv[0]),'-d [--prod] [--no-cache] [--filter <words>] [-n <to display>] [--content]'

def main():
    if '-h' in sys.argv:
        usage()
        return
    if '-d' in sys.argv:
        Flags.debugFlag = True
    debug()
    sandbox = True
    if '--prod' in sys.argv:
        sandbox = False
    if '--no-cache' in sys.argv:
        use_cache = False
    else:
        use_cache = True
    setup = ENoterSetup(sandbox=sandbox,use_cache=use_cache)
    setup.filter_words = get_arg_with('--filter')
    debug ( setup )
    enoter = ENoter(setup)
    notebooks = enoter.get_notebooks()
    if notebooks:
        for n in notebooks:
            debug('-',n.name)
    note_list = enoter.get_note_list(nlast = 20)
    debug ( note_list )
    try:
        nselect = int(str(get_arg_with('-n')))
    except:
        nselect = -1
    if note_list:
        for i,n in enumerate(note_list.notes):
            if nselect>0 and i != nselect:
                continue
            #enoter.setup.use_cache = False
            note = enoter.get_note(n.guid)
            if '--content' in sys.argv:
                print note.content.split('<en-note>')[1].split('</en-note>')[0]
            else:
                print '->',i,'Note Titled:',n.title,' GUID:',n.guid
            debug ( n )
                
    debug ('.')
    
if __name__=='__main__':
    main()
