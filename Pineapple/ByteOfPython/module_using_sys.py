import sys

print('The command line arguments are:')

for i in sys.argv:
    print i

print '\n\nThe PYTHONPATH is', sys.path, '\n'



from math import sqrt

print "Square root of 16 is", sqrt(16)


# module using name

if __name__ == '__main__' :
    print 'This program is being run by itself'
else:
    print 'I am being imported from another module'

# myModule import
import myModule

myModule.say_hi()

print 'Version :', myModule.__Version__
