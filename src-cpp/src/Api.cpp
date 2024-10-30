#define BUILDING_API_DLL

#include "Api.h"
#include "HTTPServer.h"

#include <iostream>

void sayHello()
{
    std::cout << "Hello World! I am from C++." << std::endl;
}

uint8_t startServer(uint16_t port)
{
    return (uint8_t)HttpServer::startServer(port);
}

uint8_t stopServer()
{
    return (uint8_t)HttpServer::stopServer();
}
