#pragma once
#include "Interface.h"
#include <boost/asio.hpp>
#include <iostream>
#include <string>

class Boost_Client : public Transmitter {
private:

	void send();

public:

	void run() override;

};

