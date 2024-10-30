#include "HttpServer.h"
// #include "WindowsApp.h"
// #include "utils.hpp"

#include <thread>


// 已经通过在“HttpServer.h”中定义“stopServer”函数，来实现停止服务的功能
// 因此，这里无需再在源文件中定义全局变量，然后在其它使用该全局变量的源文件
// 中以extern关键字标识的g_SERVER变量，从而实现访问该全局变量
// httplib::Server g_SERVER;

namespace HttpServer
{
    bool startServer(uint16_t port)
    {

        // // Extract values from HTTP headers and URL query params
        // g_SERVER.Get("/hi", [](const httplib::Request &req, httplib::Response &res)
        //         { res.set_content("Hello World!", "text/plain"); });

        // // Extract values from HTTP headers and URL query params
        // g_SERVER.Get("/open", [](const httplib::Request &req, httplib::Response &res)
        //     {
        //     // if (req.has_header("Content-Length")) {
        //     //     auto val = req.get_header_value("Content-Length");
        //     // }

        //     std::stringstream urlSs;
        //     if (req.has_param("file")) {
        //         auto val = req.get_param_value("file");

        //         //
        //         auto uri = createSymlink(val);
        //         urlSs << "http://" << HOST << ":" << std::to_string(PORT) << STATIC_ROUTER << uri;
        //     }

        //     // res.set_content(req.body, "text/plain");
        //     res.set_content(urlSs.str(), "text/plain");
        //     }
        // );

        // g_SERVER.Get("/filepath", [](const httplib::Request& req, httplib::Response& res)
        //     {
        //         std::string filepath = selectFileDialog();
        //         auto uri = createSymlink(filepath);

        //         //
        //         std::stringstream urlSs;
        //         urlSs << "http://" << HOST << ":" << std::to_string(PORT) << STATIC_ROUTER << uri;
        //         res.set_content(urlSs.str(), "text/plain");
        //     }
        // );

        // 前端代码静态资源访问路由
        auto ret1 = g_SERVER.set_mount_point(ROOT_ROUTER, STATIC_WEB_DIR);
        if (!ret1)
        {
            std::cout << "The specified base directory" << STATIC_WEB_DIR << "doesn't exist..." << std::endl;
        }

        // 数据、模型静态自由访问路由
        auto ret2 = g_SERVER.set_mount_point(STATIC_ROUTER, STATIC_STORE_DIR);
        if (!ret2)
        {
            std::cout << "The specified base directory" << STATIC_STORE_DIR << "doesn't exist..." << std::endl;
        }

        // SERVER.listen(HOST, port);   // 会阻塞主线程的执行

        auto thread = std::thread([&]() {
            g_SERVER.listen(HOST, port);
        });

        thread.detach();

        // Ref: https://github.com/yhirose/cpp-httplib/blob/master/test/test.cc
        //auto se = detail::scope_exit([&] {
        //    server.stop();
        //    thread.join();
        //    if (server.is_running()) {
        //        std::cerr << "Failed to shutdown server!" << std::endl;
        //    }
        //});

        g_SERVER.wait_until_ready();

        return true;
    }

    // 停止服务
    bool stopServer()
    {
        g_SERVER.stop();
        return true;
    }
}