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
	
		ignored = exec("import logging", main_namespace);
		ignored = exec("from pyftpdlib.handlers import FTPHandler", main_namespace);
		ignored = exec("from pyftpdlib.servers import FTPServer", main_namespace);
		ignored = exec("from pyftpdlib.authorizers import DummyAuthorizer", main_namespace);
		ignored = exec("authorizer = DummyAuthorizer()", main_namespace);
		ignored = exec("authorizer.add_user('user', '12345', '.', perm='elradfmwM')", main_namespace);
		ignored = exec("handler = FTPHandler", main_namespace);
		ignored = exec("handler.authorizer = authorizer", main_namespace);
		ignored = exec("logging.basicConfig(filename='/var/log/pyftpd.log', level=logging.INFO)", main_namespace);
		ignored = exec("server = FTPServer(('', 2121), handler)", main_namespace);
		ignored = exec ("server.serve_forever()", main_namespace);

		//int five_squared = extract<int>(main_namespace["result"]);
		//cout << five_squared << endl;
		
	}
	catch(error_already_set)
	{
		PyErr_Print();
	}
		
}
