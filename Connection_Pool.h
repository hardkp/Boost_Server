#pragma once
#include "Connection_Manager.h"
#include "Connection.h"

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <atomic>
#include <sstream>

#include <filesystem>
#include <fstream>

class Connection_Pool : public Connection_Manager {
private:

	unsigned thread_count = 2;

	std::vector<std::thread> threads;
	std::queue<Connection*> connections;

	std::mutex mutex;
	std::atomic_bool run_flag = false;

	std::filesystem::path get_resources_path();
	std::string get_response();

	void setup();
	void work();

	Connection* get_connection();

public:

	~Connection_Pool();
	Connection_Pool();

	void add_connection(Connection*) override;
	void del_connection(Connection*) override;

};