#include "Boost_Client.h"

void Boost_Client::send(){

	

}

void Boost_Client::run() {

	using namespace boost::asio::ip;

	boost::asio::io_context io_context;

	tcp::socket		socket{ io_context };
	tcp::endpoint	endpoint{ boost::asio::ip::address::from_string("213.171.4.39"/*"127.0.0.1"*/), 1111};
		
	while(true) try	{
		socket.connect(endpoint);
		break;
	}
	catch (std::exception& exc) {
		std::cerr << "Exc: " << exc.what() << std::endl;
	}

	while (true) try {		

		std::cout << "Input new message: ";
		std::string message; getline(std::cin, message);

		boost::asio::write(socket, boost::asio::buffer(message + '\n'));

		//----------------------------------------------------------------------------
		std::string answer;

		boost::system::error_code error_code;
		boost::asio::read_until(socket, boost::asio::dynamic_buffer(answer), '\n');

		std::cout << "Answer: " << answer << "\n";		

	}
	catch (std::exception& exc) {
		std::cout << "Exc: " << exc.what() << std::endl;
	}

	

}
