    def add_section(self, section):
        doc = yaml.load(self.stream)
        debug_obj(doc)
        print doc
        for key in doc.keys():
            print 'key is:', key, ' | object is:', doc[key]
