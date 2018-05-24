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
		object main_module ((handle<>(borrowed(PyImport_AddModule("__main__")))));
		object main_namespace = main_module.attr("__dict__");
		object ignored = exec("", main_namespace);
		
		cout << "Started the Process.." << endl;
		
		ignored = exec("server_ = raw_input(\"Please type the server to connect: \")" , main_namespace);
		ignored = exec("port_ = raw_input(\"Please type the port to connect: \")", main_namespace);
		
		ignored = exec("from ftplib import FTP", main_namespace);
		ignored = exec("ftp = FTP()", main_namespace);
		ignored = exec("ftp.connect(server_,port_)", main_namespace);
		ignored = exec("ftp.login('user','12345')",main_namespace);
		
		string response_ = "";
		while(true)
		{
			
			cout << "ftp> ";
			cin >> response_;
			if(response_ == "get")
			{
				cin.ignore();
				ignored = exec("filename_g = raw_input(\"Please type the file name: \")", main_namespace);
				ignored = exec("ftp.retrbinary('RETR %s' % filename_g, file.write)", main_namespace);
			}
			else if(response_ == "put")
			{
				cin.ignore();
				ignored = exec("filename = raw_input(\"Please type the file name: \")", main_namespace);
				ignored = exec("ftp.storbinary('STOR ' + filename, open(filename, 'rb'))", main_namespace);
			}
			else if(response_ == "ls")
			{
				ignored = exec("ftp.retrlines('LIST')", main_namespace);
			}
			else if(response_ == "lls")
			{
				ignored = exec("ftp.retrlines('LIST')", main_namespace);
			}
			else if(response_ == "quit")
			{	
				ignored = exec("ftp.quit()", main_namespace);
				break;
			}
			else
			{
				cout << "Invalid Command" << endl;
			}
		}
	}
	catch(error_already_set)
	{
		PyErr_Print();
	}
		
}
