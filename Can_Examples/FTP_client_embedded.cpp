#include <boost/python.hpp>
#include <iomanip>
#include <iostream>

using namespace boost::python;
using namespace std;


void getFile()
{
	//filename = ''
	//localfile = open(filename, 'wb')
	//ftp.retrbinary('RETR ' + filename, localfile.write, 1024)
	
	//ftp.quit()
	//localfile.close()
}

void sendFile()
{
	//filename = ''
	//ftp.storbinary('STOR ' + filename, open(filename, 'rb'))
	//ftp.quit()
}

int main (int argc, char ** argv)
{
	try
	{
		Py_Initialize();
		boost::python::object ftp_ = boost::python::import("ftplib");
		
		object main_module ((handle<>(borrowed(PyImport_AddModule("__main__")))));
		object main_namespace = main_module.attr("__dict__");
		
		object ignored = exec("", main_namespace);
		ignored = exec("from ftplib import FTP", main_namespace);
		ignored = exec("ftp = FTP('ftp.dlptest.com')", main_namespace);
		ignored = exec("ftp.login(user = 'dlpuser@dlptest.com', passwd = 'eiTqR7EMZD5zy7M')", main_namespace);
		ignored = exec("ftp.retrlines('LIST')", main_namespace);
		
		//int five_squared = extract<int>(main_namespace["result"]);
		
		cout << five_squared << endl;
		
	}
	catch(error_already_set)
	{
		PyErr_Print();
	}
		
}
