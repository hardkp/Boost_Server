#include "Web_Connection.h"

Web_Connection::Web_Connection(boost::asio::ip::tcp::socket&& socket)
	: tcp_socket{ std::make_unique<boost::asio::ip::tcp::socket>(std::move(socket)) } {	
	
}

void Web_Connection::write(std::string message){

	try	{
		boost::asio::write(*tcp_socket, boost::asio::buffer(message));
	}
	catch (std::exception& exc) {
		std::cout << "Exc: " << exc.what() << "\n";
	}

}

std::string Web_Connection::read(size_t milliseconds_timeout){

	std::string message;

	auto t1 = std::chrono::system_clock::now();

	while (true) {	

		if (tcp_socket->available()) {
			boost::asio::read_until(*tcp_socket, boost::asio::dynamic_buffer(message), "\r\n\r\n");
			return message;
		}

		auto t2 = std::chrono::system_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() >= milliseconds_timeout and milliseconds_timeout != 0) {
			throw std::runtime_error{ "Web_Connection - timeout" };
		}

	}		

	throw std::runtime_error{ "Web_Connection - Runtime error" };
}

void Web_Connection::close(){

	std::cout << "Соединение закрыто\n";

	tcp_socket->close();

}


