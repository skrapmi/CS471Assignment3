

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
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
		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
      boost::asio::streambuf response;
      boost::asio::read_until(socket, response, "\r\n");

      std::istream response_stream(&response);
      std::string sResponse;
      while (!response_stream.eof())
      {
        response_stream >> sResponse;
        cout << sResponse << " ";
      }
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

  return 0;
}
