#include <boost/python.hpp>
#include <iomanip>
#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

using namespace boost::python;
using namespace std;


int main (int argc, char ** argv)
{

	try
	{
		cout << "Python Module Starting..." << endl;
		cout << "-------------------------" << endl;
		
		Py_Initialize();
		boost::python::object ftp_ = boost::python::import("ftplib");
		
		cout << "Imported ftplib.." << endl;
		
		object main_module ((handle<>(borrowed(PyImport_AddModule("__main__")))));
		object main_namespace = main_module.attr("__dict__");
		
		cout << "Started the Process.." << endl;
		
		object ignored = exec("", main_namespace);
		
		ignored = exec("from ftplib import FTP", main_namespace);
		
		ignored = exec("ftp = FTP()", main_namespace);
		ignored = exec("ftp.connect('localhost',2121)", main_namespace);
		ignored = exec("ftp.login('user','12345')",main_namespace);
		ignored = exec("ftp.retrlines('LIST')", main_namespace);
		ignored = exec("filename = 'file_test_cpt.txt'",main_namespace);
		ignored = exec("ftp.storbinary('STOR ' + filename, open(filename, 'rb'))", main_namespace);
		ignored = exec("ftp.retrlines('LIST')", main_namespace);
		ignored = exec("ftp.quit()", main_namespace);
		
		
		//int five_squared = extract<int>(main_namespace["result"]);
		//cout << five_squared << endl;
		
	}
	catch(error_already_set)
	{
		PyErr_Print();
	}
		
}
