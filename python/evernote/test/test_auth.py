#!/usr/bin/env python

import sys

#from evernote.api.client import EvernoteClient
import evernote.api.client as enClient
import evernote.edam.type.ttypes as enTypes
import evernote.edam.error.ttypes as enErrors

import traceback
def debug(*msg):
    stack = traceback.extract_stack()
    filename, codeline, funcName, text = stack[-2]
    #return funcName
    msg_str = []
    if len(msg) == 0:
        msg_str.append('begin')
    else:
        for e in msg:
            msg_str.append(str(e))
    if msg_str[0] == '.':
        msg_str[0] = 'done.'
    if msg_str[0] == '-':
        msg_str[0] = ''
        print '   ',funcName,':',' '.join(msg_str)
    else:
        if msg_str[0] == 'e':
            msg_str.remove(msg_str[0])
            print '[error]',funcName,':',' '.join(msg_str)            
        else:
            print '[d]',funcName,':',' '.join(msg_str)

def get_client(dev_token, sandbox=True):
    debug( )
    client = enClient.EvernoteClient(token=dev_token)
    debug( 'got client', client )
    return client

def test_auth(client):
    userStore = client.get_user_store()
    debug('got userStore',userStore)
    try:
        user = userStore.getUser()
        debug('user',user.username)
    except enErrors.EDAMSystemException as edue:
        debug('e','unable to getUser; error is:',edue)
    debug('.')

def get_note_store(client):
    try:
        noteStore = client.get_note_store()
    except enErrors.EDAMSystemException as edue:
        debug('e','unable to get_note_store; error is:',edue)
        return None
    return noteStore

def get_linked_notebooks(client, auth_token):
    # get linked notebooks
    #userStore = client.get_user_store()
    noteStore = get_note_store(client)
    if noteStore == None:
        return
    linked_notebooks = noteStore.listLinkedNotebooks(auth_token)
    debug('linked notebooks:')
    for nb in linked_notebooks:
        debug('-',nb)
    debug('.')

def print_notebooks(client):
    debug()
    noteStore = get_note_store(client)
    if noteStore == None:
        return
    notebooks = noteStore.listNotebooks()
    debug('notebooks:')
    for n in notebooks:
        debug('-',n.name)

def create_note(client):
    noteStore = get_note_store(client)
    if noteStore == None:
        return
    note = enTypes.Note()
    note.title = "I'm a test note!"
    note.content = '<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE en-note SYSTEM "http://xml.evernote.com/pub/enml2.dtd">'
    note.content += '<en-note>Hello, world!</en-note>'
    note = noteStore.createNote(note)

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
if __name__=='__main__':
    token = dev_token
    if '--prod' in sys.argv:
        token = prod_token
    sandbox = True
    if token == dev_token:
        sandbox = True
    if token == prod_token:
        sandbox = False
    sandbox = False        
    debug('sandbox:',sandbox)
    client = get_client(token, sandbox=sandbox)
    test_auth(client)
    print_notebooks(client)
    create_notebook(client)
    print_notebooks(client)
    get_linked_notebooks(client, token)
