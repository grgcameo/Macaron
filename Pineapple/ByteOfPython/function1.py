# function define
def say_hello():
    print 'hello world'


say_hello()
say_hello()


# function with param
def print_max(a, b):
    if a > b:
        print a, 'is maximum'
    elif a == b:
        print a, 'is equal to', b
    else:
        print b, 'is maximum'  


print_max(3, 4)

x = 5
y = 2

print_max(x, y)

# local variable

x = 50

def func(x):
    print 'x is', x
    x = 2
    print 'Change local x to', x

func(x)

print 'x is still', x


# function global variable

z = 60

def global_func():
    global z

    print 'z is', z
    z = 2
    print 'Change global z to', z

global_func()
print 'Value of z is', z


# default param


def default_say(message, times = 1):
    print message * times

default_say('hello')
default_say('World', 5)


# keyword argument

def keyword_func(a, b = 5, c = 10):
    print 'a is', a, 'and b is', b, 'and c is', c

keyword_func(3, 7)
keyword_func(25, c = 24)
keyword_func(c = 50, a = 100)
keyword_func(b = 50, c = 100, a = 1)

# VarArgs param

def total(initial = 5, *numbers, **keywords):
    count = initial
    for number in numbers:
        count += number

    for key in keywords:
        count += keywords[key]

    return count

print total(10, 1, 2, 3, vegetabnle = 50, fruits = 100)


# docString

def docString_max(p, q):
    '''Prints the maximum of two numbers.

    The two values must be integers.'''
    
    #convert to integers, if possible
    p = int(p)
    q = int(q)

    if p > q:
        print p, 'is maximum'
    else:
        print q, 'is maximum'

docString_max(3, 5)
print docString_max.__doc__

help(docString_max)
