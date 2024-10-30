#include "HttpServer.h"
#include "WindowsApp.h"
#include "utils.hpp"

// int main()
//{
//     httplib::Server server;
//
//     // Extract values from HTTP headers and URL query params
//     server.Get("/hi", [](const httplib::Request& req, httplib::Response& res) {
//         res.set_content("Hello World!", "text/plain");
//         });
//
//     // Extract values from HTTP headers and URL query params
//     server.Get("/open", [](const httplib::Request& req, httplib::Response& res) {
//         // if (req.has_header("Content-Length")) {
//         //     auto val = req.get_header_value("Content-Length");
//         // }
//
//         std::stringstream urlSs;
//         if (req.has_param("file")) {
//             auto val = req.get_param_value("file");
//
//             //
//             auto uri = createSymlink(val);
//             urlSs << "http://" << HOST << ":" << std::to_string(PORT) << STATIC_ROUTER << uri;
//         }
//
//         // res.set_content(req.body, "text/plain");
//         res.set_content(urlSs.str(), "text/plain");
//         });
//
//     // 前端代码静态资源访问路由
//     auto ret1 = server.set_mount_point(ROOT_ROUTER, STATIC_WEB_DIR);
//     if (!ret1) {
//         std::cout << "The specified base directory" << STATIC_WEB_DIR << "doesn't exist..." << std::endl;
//     }
//
//     // 数据、模型静态自由访问路由
//     auto ret2 = server.set_mount_point(STATIC_ROUTER, STATIC_STORE_DIR);
//     if (!ret2) {
//         std::cout << "The specified base directory" << STATIC_STORE_DIR << "doesn't exist..." << std::endl;
//     }
//
//     server.listen(HOST, PORT);
//
//     return 0;
// }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow)
{
    // 启动服务
    if (!startServer()) {
        std::cerr << "Failed to start server!" << std::endl;
        return -1;
    }

    // 使用系统默认浏览器打开服务地址
    loadUrlByDefaultBrowser();

    // 注册窗口类和创建窗口等...
    createWindow(hInstance);

    // 消息循环
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}
