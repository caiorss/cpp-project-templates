/*  Caio Rodrigues 
 *  Description: Basic boost asio server. 
 *
 ************************************************ */

#include <ctime>
#include <iostream>
#include <string>
#include <memory>
#include <functional>

#include <boost/asio.hpp>

using boost::asio::io_context;
using boost::asio::ip::tcp;
using error_code = boost::system::error_code;
using socket_ptr = std::shared_ptr<tcp::socket>;

using client_handler = std::function<void (error_code, std::shared_ptr<tcp::socket>)>;

class tcp_server
{
	unsigned short           m_port;
	boost::asio::io_context& m_ioctx;
	tcp::acceptor            m_acceptor;
	client_handler           m_client_handler;

public:

	tcp_server(unsigned short port, io_context& io_context, client_handler handler)
		: m_port(port), m_ioctx(io_context)
		, m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
		, m_client_handler(handler)
	{
		std::puts(" [INFO] Start server. OK.");
		this->start_accept();
	}

private:

	void start_accept()
	{
		auto client = std::make_shared<tcp::socket>(m_ioctx);
		m_acceptor.async_accept(
            *client
			, [this, client](error_code const& err)
			{
				m_client_handler(err, client);
				// Accept a new connection
				start_accept();
			}
			);
	} // ---- End of start_accept() ---

};


struct session_data
{
	std::string message;
	boost::asio::streambuf input_buffer;
};

void session_handler(socket_ptr client)
{

	// If the session data is allocated on the stack, a memory leak happens.
	auto data = std::make_shared<session_data>();

	// Read input until user types RETURN or '\n' new line char from
	// netcat side.
	boost::asio::async_read_until(
        *client, data->input_buffer, "\n"
		,[=]( error_code const& err,  size_t bytes_transferred)
		{
			// if(err){ return; }

			std::puts(" [INFO] Finish reading user input");

			std::istream ins(&data->input_buffer);
			std::ostringstream ss;
			ss << ins.rdbuf();
			data->message = ss.str();

			std::cout << " [INFO] Received text = " << data->message << std::endl;

			if(data->message == "quit\n"){
				std::puts(" [INFO] Exit session");
				client->close();
				return;
			}

			data->message = " ECHO => " + data->message;

			// Write output back in async way
			boost::asio::async_write(
				// Socket destination to where the message will be sent
                *client
				// Buffer to be sent
				, boost::asio::buffer(data->message),
				// Error handler
				[=]( error_code const& err,  size_t bytes_transferred)
				{
					std::cerr << " [TRACE] <WRITE> Bytes transferred =  "
							  << bytes_transferred
							  << std::endl;

					// Loop session
					session_handler(client);
				});

		}); // End of boost::asio::async_read_until callback

}

int main()
{    
	try
	{
		auto io_context = boost::asio::io_context{};
		auto acceptor   = tcp::acceptor{io_context};

		std::cout << " [INFO] Current PID = " << ::getpid() << std::endl;

		tcp_server server(
            9078, io_context
			, [&](  error_code const& err, socket_ptr client)
			{
				std::cerr << " [TRACE] Connection accepted from IP = "
						  << client->remote_endpoint().address().to_string()
						  << "\n";

				session_handler(client);

				// this->handle_accept(conn, err);

			}); // --- End of server() instantiation --- //

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::puts(" [INFO] Server stopped OK");

	return 0;
}

