#pragma once
#include <string>

class Connection {
public:
	virtual ~Connection() = default;
	virtual void write(std::string message) = 0;
	virtual std::string read(size_t milliseconds_timeout = 0) = 0;	
	virtual void close() = 0;
};