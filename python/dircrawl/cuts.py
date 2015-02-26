    def add_section(self, section):
        doc = yaml.load(self.stream)
        debug_obj(doc)
        print doc
        for key in doc.keys():
            print 'key is:', key, ' | object is:', doc[key]


    def process_by_name(self):
        t = self.pop_tag_named('Title:')
        if t != None:
            self.title = ''.join(t.content)
        t = self.pop_tag_named('Subtitle:')
        if t != None:
            self.subtitle = ''.join(t.content)
        t = self.pop_tag_named('Content:')
        if t != None:
            self.content = '\n'.join(t.content)


def load_stream_to_docs(stream):
    tag = None    
    docs = []
    current_doc = []
    for l in stream:
        for k in Config.KEYWORDS:
            if k == l[:len(k)]:
                if tag:
                    current_doc.append(tag)
                if k == '- ':
                    key = 'Content:'
                else:
                    key = k
                tag = Tag(key)
        if tag:
            if tag.key == '...':
                docs.append(current_doc)
                current_doc = []
                tag = None
                continue
            if tag.key == l[:len(tag.key)]:
                s = l[len(tag.key):].strip('\n')
            else:
                s = l.strip('\n')
            if len(s) > 0:
                tag.append(s)
    if tag:
        current_doc.append(tag)
    if len(current_doc) > 0:
        docs.append(current_doc)
    return docs

def load_file(fname):
    with open(fname) as f:
        stream = f.readlines()
    #print stream
    docs = load_stream_to_docs(stream)
    #debug_obj(docs)
    for i,doc in enumerate(docs):
        #print i,doc
        #for tag in doc:
        #    print 'key is:', tag.key, ' | object is:', tag.content
        print '---------'
        s = Section(doc)
        #s.process()
        #print 'title:', s.pop_tag_key('Title:').content
        #print 'sub:', s.pop_tag_key('Subtitle:').content        
        #debug_obj(s)
        #print i, s
        print s.render()

def main():
    load_file('testinput.txt')
    #s = Section(testin)
    #print
    #print s.render()
    
if __name__ == '__main__':
    main()
