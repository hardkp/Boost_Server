#include "Connection_Pool.h"

Connection_Pool::~Connection_Pool(){

	run_flag = false;
	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}

}

Connection_Pool::Connection_Pool(){
	setup();
}

std::filesystem::path Connection_Pool::get_resources_path(){
	
	auto current_path = std::filesystem::current_path();
	while (true) {		

		for (auto& dir : std::filesystem::directory_iterator(current_path)) {
			
			if (dir.path().filename() == "Resources") {

				return current_path / "Resources";
			}

		}

		if (current_path != current_path.root_path()) {
			current_path = current_path.parent_path();
		}
		else {
			throw
				std::runtime_error{ "Connection_Pool - Resources path is not found" };
		}

	}	
}

std::string Connection_Pool::get_response(){
	
	std::filesystem::path resources_path = get_resources_path();
	std::cout 
		<< "Res path: " << resources_path << "\n";

	//--------------------------------------------------------
	std::ifstream file{ resources_path / "index.html" };

	if (!file.is_open()) {
		throw std::runtime_error{ "Connection_Pool - file is not open" };
	}

	std::string html{ std::istreambuf_iterator<char>(file), {} };		
	file.close();	

	std::string response{
			"HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: " + std::to_string(html.size()) + "\r\n\r\n" + html
	};

	return response;
}

void Connection_Pool::setup() {

	run_flag = true;
	for (int i = 0; i < thread_count; ++i)	{
		threads.push_back(std::thread{ &Connection_Pool::work, this });
	}
}

void Connection_Pool::work(){
		
	while (run_flag) try {		

		std::unique_ptr<Connection>	connection{ get_connection() };

		auto message = connection->read(8000);
		std::cout << "Msg: " << message << "\n";		
		
		std::string response = get_response();		

		connection->write(response);
		connection->close();

		std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });

	}
	catch (std::exception& exc) {
		std::cout << "Exc: " << exc.what() << "\n";
	}

}

Connection* Connection_Pool::get_connection(){

	while (run_flag) {

		std::unique_lock<std::mutex> lock{ mutex };

		if (!connections.empty()) {

			auto connection = connections.front();
			connections.pop();
			return connection;
		}		
		std::this_thread::sleep_for(std::chrono::milliseconds{ 1 });
	}

	throw std::runtime_error{ "Connection_Pool - Run flag = false" };
	
}

void Connection_Pool::add_connection(Connection* new_connection){

	std::cout << "Новое соединение\n";
	std::unique_lock<std::mutex> lock{ mutex };
	connections.push(new_connection);

}

void Connection_Pool::del_connection(Connection*){
}
