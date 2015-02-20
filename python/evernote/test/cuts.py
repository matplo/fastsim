# your local dir: /opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/evernote


                if t.mro()[1] == object:
                    retval.append(str(t) + ' ' + name + ' = ' + str(value) )


from optparse import OptionParser
import inspect

    def __repr__(self):
        inspect_members = inspect.getmembers(ENoterSetup, predicate=inspect.iscode) #inspect.isclass) #, predicate=inspect.is
        retval = []
        #print inspect_members
        for e in inspect_members:
            print e
            #retval.append(str(e))
        return ' '.join(retval)

    def __repr__(self):
        print self.__dict__.keys()

        ---


class test_class:
    def test(self):
        debug( 'test text')        
def test_debug():
    debug( 'test text')

test_debug()
test_class().test()
            
