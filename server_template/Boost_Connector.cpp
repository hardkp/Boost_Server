#include "Boost_Connector.h"

Boost_Connector::~Boost_Connector(){

}

Boost_Connector::Boost_Connector(Connection_Manager* _connection_manager, size_t _port_number)
	: connection_manager{ _connection_manager }, port_number{ _port_number } {

	setup();
}

void Boost_Connector::setup() {

	io_context 
		= std::make_unique<boost::asio::io_context>();
	
}

void Boost_Connector::set_connection_manager(Connection_Manager* _connection_manager) {	
	
	if (!run_flag) {
		connection_manager = _connection_manager;
	}
	else {
		throw std::runtime_error{ 
			"Boost_Connector - It is not possible to change the connection manager that is used." };
	}

}

void Boost_Connector::run() {	

	if (!run_flag) {

		boost::asio::ip::tcp::endpoint endpoint{ boost::asio::ip::tcp::v4(), static_cast<unsigned short/*boost::asio::ip::port_type*/>(port_number) };

		acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(
			*io_context,
			endpoint
		);		

		run_flag = true;
		thread = std::make_unique<std::thread>(&Boost_Connector::work, this);

	}
	else {
		throw
			std::runtime_error{ "Boost_Connector - The connector cannot be turned on" };
	}

}

void Boost_Connector::work(){ //можно ли пометить noexcept?
		
	std::stringstream stream;
	stream << port_number << " - port";

	std::cout
		<< "--------------------------------\n"
		<< "Server is listening: " << stream.str() << "\n"
		<< "--------------------------------\n";

	std::unique_lock<std::mutex> lock{ mutex };
	while (true) try {

		boost::asio::ip::tcp::socket socket{ *io_context };
		acceptor->accept(socket);

		std::cout << "New connection\n";
		
		if (connection_manager) {
			connection_manager->add_connection(new Web_Connection{ std::move(socket) });
		}
		else {
			throw 
				std::runtime_error{ "Boost_Connector - New connection is lost" };
		}

	}
	catch (std::exception& exc) {

		std::cout << "Exc: " << exc.what() << "\n";			
		
		if (typeid(boost::wrapexcept<class boost::system::system_error>)
			== typeid(exc)) {			
			break;
		}
		
	}	

}

void Boost_Connector::stop(){
	
	if (run_flag) {

		if (acceptor){
			acceptor->close();
			std::unique_lock<std::mutex> lock{ mutex };			
			acceptor.reset();
		}

		if (thread and thread->joinable()) {
			thread->join();
			thread.reset();
		}

		run_flag = false;
		std::stringstream stream;
		stream << port_number << " - port";

		std::cout
			<< "--------------------------------\n"
			<< "Server is stop: " << stream.str() << "\n"
			<< "--------------------------------\n";

	}	
	else {
		throw 
			std::runtime_error{ "Boost_Connector - The connector cannot be turned off" };
	}	

}
