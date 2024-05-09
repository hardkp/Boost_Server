#pragma once
#include "Connector.h"
#include "Connection_Manager.h"

#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <memory>
#include <thread>

#include "Web_Connection.h"

class Boost_Connector : public Connector {
private:

	size_t port_number;	

	Connection_Manager* connection_manager = nullptr;

	std::unique_ptr<boost::asio::io_context> io_context;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
	std::unique_ptr<std::thread> thread;

	std::mutex mutex;
	bool run_flag = false;

	void setup();	
	void work();

public:

	~Boost_Connector();
	Boost_Connector(Connection_Manager*, size_t port_number);

	void set_connection_manager(Connection_Manager*) override;

	void run() override;
	void stop() override;

};
