# coding: cp932 
'''py_function.py - Python source designed to
demonstrate the use of python embedding'''

def multiply():
    c = 12345*6789
    print 'The reuslt of 12345 x 6789:', c
    return c
def witharg(i):
    print '%d x %d is %d' % (i,i,i * i)

def withstr(s):
    print '%s' % s


def splitter(s):
    for line in s:
        while line != []:
            print(line[:33]+"\n");
            line = "" 
