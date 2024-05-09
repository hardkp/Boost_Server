#pragma once
#include <string>
#include <memory>

template <typename Socket>
class Connection_Manager_Old {
public:
	virtual ~Connection_Manager_Old() = default;
	virtual void add_new_connection(Socket&&) = 0;
};

//-------------------------------------------------------------------------------

class Transmitter {
public:
	virtual ~Transmitter() = default;
	virtual void run() = 0;	
};

//-------------------------------------------------------------------------------

template <typename Data>
class Validator {
public:
	virtual ~Validator() = default;
	virtual bool to_validate(Data) = 0;
};

template <typename Data, typename Result>
class Parser {
public:
	virtual ~Parser() = default;
	virtual Result to_parse(Data) = 0;
};

class Handler {
public:
	virtual ~Handler() = default;
	virtual void execute() = 0;
};
