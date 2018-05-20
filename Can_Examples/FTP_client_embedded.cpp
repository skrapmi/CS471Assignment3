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
		string FTP_server = "ftp.dlptest.com";
		string FTP_user   = "dlpuser@dlptest.com";
		string FTP_pass   = "eiTqR7EMZD5zy7M";
		
		string FTP_server_pub = "ftp.uconn.edu";
		string FTP_port_pub   = "21";
		
		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);

		tcp::resolver::query __QUERY__(FTP_server_pub, FTP_port_pub);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(__QUERY__);
		tcp::resolver::iterator end;
		
		tcp::socket socket(io_service);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while(error && endpoint_iterator != end)
		{
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if(error) { throw boost::system::system_error(error);}
		if(!error) 
		{ 
	
			cout << "socket connected: " << socket.is_open() << endl;
			
			boost::asio::streambuf response;
		  boost::asio::read_until(socket, response, "\r\n");

		  std::istream response_stream(&response);
		  std::string sResponse;
		  while (!response_stream.eof())
		  {
			response_stream >> sResponse;
			cout << sResponse << " ";
		  }
		  
		  cout << endl;
		  io_service.run();
		}
		else
		{
		  cout << "Error: " << error.message() << endl;
		}
	}
	catch (std::exception& e)
	{
    std::cerr << e.what() << std::endl;
	}
	
	try
	{
		cout << "Python Module Starting..." << endl;
		cout << "-------------------------" << endl;
		

		Py_Initialize();
		boost::python::object ftp_ = boost::python::import("ftplib");
		
		object main_module ((handle<>(borrowed(PyImport_AddModule("__main__")))));
		object main_namespace = main_module.attr("__dict__");
		object ignored = exec("", main_namespace);
		
		ignored = exec("from ftplib import FTP", main_namespace);
		//ignored = exec("ftp = FTP('ftp.dlptest.com')", main_namespace);
		//ignored = exec("ftp.login(user = 'dlpuser@dlptest.com', passwd = 'eiTqR7EMZD5zy7M')", main_namespace);
		//ignored = exec("ftp.retrlines('LIST')", main_namespace);
		
		ignored = exec("ftp = FTP('ftp.uconn.edu')", main_namespace);
		ignored = exec("ftp.login()", main_namespace);
		ignored = exec("ftp.retrlines('LIST')", main_namespace);
		ignored = exec("ftp.cwd('48_hour')", main_namespace);
		ignored = exec("ftp.retrlines('LIST')", main_namespace);
		
		string menu_selection = "put";
		
		if(menu_selection == "get")
		{
			
		}
		else if(menu_selection == "put")
		{
			ignored = exec("filename = 'file_test_cpt.txt'",main_namespace);
			ignored = exec("ftp.storbinary('STOR ' + filename, open(filename, 'rb'))", main_namespace);
			ignored = exec("ftp.retrlines('LIST')", main_namespace);
			ignored = exec("ftp.quit()", main_namespace);
		}
		
		



		
		//int five_squared = extract<int>(main_namespace["result"]);
		
		//cout << five_squared << endl;
		
	}
	catch(error_already_set)
	{
		PyErr_Print();
	}
		
}
