#pragma once
#include "Connection.h"

class Connection_Manager {
public:
	virtual ~Connection_Manager() = default;
	virtual void add_connection(Connection*) = 0;
	virtual void del_connection(Connection*) = 0;
};