Required libraries to compile the project:

* Boost library
* Python Library
* Pyftpdlib Library

If pyconfig.h error please link pyconfig.h to gcc:

* You can find your own python include path by using find /usr/include -name pyconfig.h, in my case this returns:
  * /usr/include/python2.7/pyconfig.h
  * /usr/include/i386-linux-gnu/python2.7/pyconfig.h

* Aleternatively appending -I /usr/include/python2.7/ should fix it.
* In addition (this is the method i use) you can add the directory to your path with:
  * export CPLUS_INCLUDE_PATH="$CPLUS_INCLUDE_PATH:/usr/include/python2.7/"

Compile Segment consists of for now:

* g++ <program_name.cpp> -o <output_file_name> -std=c++11 -lboost_python -lpython2.7 -lboost_system -lboost_thread -lpthread
* g++ FTP_server_embedded.cpp -o ftp_server -std=c++11 -lboost_python -lpython2.7 -lboost_system -lboost_thread -lpthread
* g++ FTP_client_embedded.cpp -o ftp_client -std=c++11 -lboost_python -lpython2.7 -lboost_system -lboost_thread -lpthread

To run each program you must be calling sudo ./<file_name_to_run>
