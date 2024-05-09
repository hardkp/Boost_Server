#pragma once
#include "Connection.h"

#include <iostream>
#include <chrono>
#include <boost/asio.hpp>

class Web_Connection : public Connection{
private:

	std::unique_ptr<boost::asio::ip::tcp::socket> tcp_socket;	

public:

	Web_Connection(boost::asio::ip::tcp::socket&&);

	void write(std::string message) override;
	std::string read(size_t milliseconds = 0) override;
	void close() override;

};