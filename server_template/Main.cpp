#include <iostream>
#include <thread>

#include "Boost_Connector.h"
#include "Connection_Pool.h"

int main(){
    setlocale(LC_ALL, "rus");  

    Connection_Pool pool;

    Boost_Connector connector{ &pool, 1111 };
    connector.run();      
   
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds{ 2 });
    }

    return 0;
}


