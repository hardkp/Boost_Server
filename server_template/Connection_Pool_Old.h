#pragma once

#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <queue>
#include <ranges>
#include <atomic>
#include <iostream>

#include "Interface.h"

class Connection_Pool_Old : 
	public Connection_Manager_Old<boost::asio::ip::tcp::socket>{
private:

	std::vector<std::thread> threads;
	std::queue<boost::asio::ip::tcp::socket> new_sockets;
	std::mutex mutex_new_sockets;
	std::atomic_bool run;

	bool time_out(std::chrono::system_clock::time_point, size_t delay);

	Validator<std::string>* validator = nullptr; //определиться с интерфейсом

public:

	void add_new_connection(boost::asio::ip::tcp::socket&&) override ;
	void connection_handler();	

	Connection_Pool_Old();
	~Connection_Pool_Old();

};

