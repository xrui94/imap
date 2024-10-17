#include "WindowApp.h"
#include "HttpServer.h"
#include "utils.hpp"

#include <commdlg.h>

// 已经通过在“HttpServer.h”中定义“stopServer”函数，来实现停止服务的功能
// 因此，这里不再直接使用extern标识的g_SERVER变量
// extern httplib::Server SERVER;

// 窗口过程函数
LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_TRAYICON:
    {
        // 处理鼠标左键双击、或鼠标右键单击托盘图标时的消息
        if (lParam == WM_RBUTTONDOWN)
        {
            POINT pt;
            GetCursorPos(&pt);
            SetForegroundWindow(hWnd);
            TrackPopupMenu(hTrayMenu, TPM_BOTTOMALIGN | TPM_RIGHTALIGN, pt.x, pt.y, 0, hWnd, NULL);
            PostMessage(hWnd, WM_NULL, 0, 0);
        }
        else if (lParam == WM_LBUTTONDBLCLK)
        {
            loadUrlByDefaultBrowser();  // 使用系统默认浏览器打开服务地址
        }
        break;
    }
    case WM_COMMAND:
    {
        // 处理菜单命令
        switch (LOWORD(wParam))
        {
        case 1:
        {
            // 打开
            // ShowWindow(hWnd, SW_RESTORE);   // 打开窗口
            loadUrlByDefaultBrowser();  // 使用系统默认浏览器打开服务地址
            break;
        }
        case 2:
        {
            // 退出
            PostQuitMessage(0);
            break;
        }
        }
        break;
    }
    case WM_DESTROY:
    {
        // 停止服务
        stopServer();

        // 销毁窗口
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;
    }
    case WM_SHOWMAINWND:
    {
        ShowWindow(hWndMain, isWindowVisible ? SW_SHOW : SW_HIDE);
        break;
    }
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

void createWindow(HINSTANCE hInstance)
{
    // 注册窗口类(WNDCLASS是老版本)
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX); // 必须设置这个成员的大小
    wc.style = 0;
    wc.lpfnWndProc = wndProc; // 您的窗口过程函数
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;                      // 应用程序实例句柄
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);    // 加载图标
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);      // 加载光标
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 背景画刷
    wc.lpszMenuName = NULL;                        // 菜单名（通常为NULL）
    wc.lpszClassName = CLASS_NAME;                 // 窗口类名
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  // 小图标（可选）
    // 注册窗口类
    if (!RegisterClassEx(&wc))
    {
        // 处理注册失败的情况
        MessageBoxW(NULL, L"Call to RegisterClassEx failed!", L"Win32 Guided Tour", NULL);
        return;
    }

    // 创建窗口
    hWndMain = CreateWindowEx(
        0,
        CLASS_NAME,
        "Tray Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        200,
        100,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hWndMain == NULL)
    {
        return;
    }

    // 最小化到任务栏托盘
    // ShowWindow(hWndMain, SW_MINIMIZE);
    ShowWindow(hWndMain, SW_HIDE);
    UpdateWindow(hWndMain);

    // 初始化托盘图标数据
    // NOTIFYICONDATA nid = { 0 };
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWndMain;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    lstrcpy(nid.szTip, "Minimize To Tray");

    // 创建托盘右键菜单
    hTrayMenu = CreatePopupMenu();
    AppendMenuW(hTrayMenu, MF_STRING, 1, TRAY_MENU_OPEN);
    AppendMenuW(hTrayMenu, MF_STRING, 2, TRAY_MENU_EXIT);

    Shell_NotifyIcon(NULL, &nid);
}

std::string selectFileDialog()
{
    // 初始化OPENFILENAME结构体
    OPENFILENAME ofn = {0};
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = new char[260];
    ofn.lpstrFile[0] = L'\0';
    ofn.nMaxFile = 260;
    // ofn.lpstrFilter = L"3DTiles模型 (*.json)\0*.json\0GLTF模型 (*.gltf;*.glb)\0*.gltf;*.glb\0All Files\0*.*\0";
    const char* filter[] = {
        "3DTiles模型 (*.json)",
        "*.json",
        "GLTF模型 (*.gltf;*.glb)",
        "*.gltf;*.glb",
        "所有文件 (*.*)",
        "*.*",
        NULL
    };
    ofn.lpstrFilter = filter[0];
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

    // 打开文件选择对话框
    if (GetOpenFileName(&ofn))
    {
        // 获取选择的文件路径
        std::string filePath = ofn.lpstrFile;
        // ...

        // 释放资源
        delete[] ofn.lpstrFile;

        return std::string(filePath);
    }
    else
    {
        // 获取错误代码
        DWORD errorCode = CommDlgExtendedError();
        // ...
        std::cerr << "选择文件时, 发生错误!" << std::endl;
    }
}
