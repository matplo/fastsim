#!/usr/bin/env python

import sys
import evernote.api.client as enClient
import evernote.edam.notestore as enStore
import evernote.edam.type.ttypes as enTypes
import evernote.edam.error.ttypes as enErrors
from utils import *

import datetime
    
class ENoterSetup:
    default_dev_token  = 'S=s1:U=904fb:E=152ac1870e0:C=14b54674120:P=1cd:A=en-devtoken:V=2:H=1993fecb1c0c1cf6158801c186d0e51d'
    default_prod_token = 'S=s44:U=4a1a5a:E=152ac4525a7:C=14b5493f670:P=1cd:A=en-devtoken:V=2:H=f76e7e0a01f049e12e9748e82bde0cbe'
    default_c_secret   = '9f451936519fb24e'
    default_c_key      = 'ploskon'
    default_sandbox    = True
    
    def __init__(self, **args):        
        self.c_secret = not_none(self.default_c_secret,  args.get('c_secret'))
        self.c_key    = not_none(self.default_c_key,     args.get('c_key'))
        self.sandbox  = not_none(self.default_sandbox,   args.get('sandbox'))
        self.token    = args.get('token')
        if self.token == None:
            if self.sandbox == True:
                self.token = self.default_dev_token
            else:
                self.token = self.default_prod_token
                
    def __repr__(self):
        return '[i] EnoterSetup:\n' + Inspector(self).table_members_basic()

class ENoter:
    def __init__(self, setup):
        self.setup      = setup
        self.reset()
        
    def reset(self):
        self.client     = None
        self.user_store = None
        self.user       = None
        self.note_store = None
        
    def get_client(self):
        debug( )
        if self.client == None:
            self.client = enClient.EvernoteClient(sandbox=setup.sandbox,
                                                token=setup.token,
                                                consumer_key=setup.c_key,
                                                consumer_secret=setup.c_secret)
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
            self.note_store = self.client.get_note_store()
        except enErrors.EDAMSystemException as edue:
            debug('e','unable to get_note_store; error is:',edue)
            return None
        debug_obj ( self.note_store )
        return self.note_store

    def get_notebooks(self):
        try:
            self.notebooks = self.get_note_store().listNotebooks()
        except enErrors.EDAMSystemException as edue:
            debug('e','unable to get notebooks; error is:',edue)
            return None
        #debug_obj(self.notebooks)
        for n in self.notebooks:
            debug('-',n.name)
        return self.notebooks

    def create_note(self, title, contents):
        noteStore = self.get_note_store()
        if noteStore == None:
            debug('e', 'unable to create a note!')
            return
        note = enTypes.Note()
        note.title = title
        note.content = '<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE en-note SYSTEM "http://xml.evernote.com/pub/enml2.dtd">'
        note.content += '<en-note>' + contents + '</en-note>'
        created_note = noteStore.createNote(note)
        print "Successfully created a new note with GUID: ", created_note.guid

    def read_notes(self, nlast = 3):
        noteStore = self.get_note_store()
        if noteStore == None:
            debug('e', 'unable to create a note!')
            return

        flter = enStore.NoteStore.NoteFilter()
        flter.ascending = False
 
        spec = enStore.NoteStore.NotesMetadataResultSpec()
        spec.includeTitle = True
 
        ourNoteList = noteStore.findNotesMetadata(flter, 0, nlast, spec)
        for n in ourNoteList.notes:
            debug_obj ( n )
            #print n.title
        
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
    
if __name__=='__main__':
    sandbox = True
    if '--prod' in sys.argv:
        sandbox = False
    setup = ENoterSetup(sandbox=sandbox)
    #print Inspector(setup).table_members_all()
    debug ( setup )
    enoter = ENoter(setup)
    enoter.get_client()
    enoter.get_user()
    notebooks = enoter.get_notebooks()
    if '--create-test-note' in sys.argv:
        enoter.create_note('test note at:' + str(datetime.datetime.now()), 'content from python...')
    enoter.read_notes()
    debug ('.')
