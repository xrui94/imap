#pragma once

#include <httplib.h>

// 常量定义
constexpr const char *ROOT_ROUTER = "/";
constexpr const char *STATIC_ROUTER = "/static";
constexpr const char *STATIC_WEB_DIR = STATIC_DIR "/web";
constexpr const char *STATIC_STORE_DIR = STATIC_DIR "/store";
constexpr const char *HOST = "localhost";
constexpr uint16_t PORT = 1027;

// 应该写在源文件中，避免该头文件被多个源文件包含时，编译出现变量重复定义的问题
// 在源文件中定义全局变量，在其他源文件中，可以通过加上“extern”关键字声明该变量，以便访问。
// httplib::Server g_SERVER;

// 由于使用了“stopServer”方法，其它源文件中不再直接使用g_SERVER变量，
// 因此，这里声明为static全局变量，这样确保
// 只有在“HTTPServer.h”和“HTTPServer.cpp”文件中可用
static httplib::Server g_SERVER;

bool startServer();

void stopServer();
