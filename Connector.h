#pragma once
#include "Connection_Manager.h"

class Connector {
public:
	virtual ~Connector() = default;	
	virtual void set_connection_manager(Connection_Manager*) = 0;
	virtual void run() = 0;
	virtual void stop() = 0;
};