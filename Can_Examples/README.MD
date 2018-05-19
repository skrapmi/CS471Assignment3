Requirements to compile the project
Boost library
Python Library

You can find your own python include path by using find /usr/include -name pyconfig.h, in my case this returns:

/usr/include/python2.7/pyconfig.h
/usr/include/i386-linux-gnu/python2.7/pyconfig.h

so appending -I /usr/include/python2.7/ should fix it, alternatively you can add the directory to your path with:
export CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH:/usr/include/python2.7/"
