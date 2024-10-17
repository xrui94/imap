#pragma once

#define WIN32_LEAN_AND_MEAN // 该宏定义须加上，否则，Windows.h头文件应该放到httplib.h后
#include <Windows.h>
#include <Windowsx.h>
#include <shellapi.h>

#include <string>

#define WM_TRAYICON (WM_USER + 1)
#define WM_SHOWMAINWND (WM_USER + 2)

static const char *CLASS_NAME = "TrayWindowClass";
static const wchar_t *TRAY_MENU_OPEN = L"打开";
static const wchar_t *TRAY_MENU_EXIT = L"退出";
static HWND hWndMain;
static HMENU hTrayMenu;
static NOTIFYICONDATA nid;
static BOOL isWindowVisible = FALSE;


LRESULT CALLBACK wndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void createWindow(HINSTANCE hInstance);

std::string selectFileDialog();
