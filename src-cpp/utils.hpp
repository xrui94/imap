#pragma once

#include <Windows.h>

#include <string>
#include <sstream>
#include <iostream>
#include <filesystem>


static std::string wcharToString(WCHAR* filepath)
{
     // WCHAR*字符串
    // WCHAR* wstr = L"Hello, World!";

    // 转换为std::wstring
    std::wstring wstring(filepath);

    // 转换为std::string
    std::string str(wstring.begin(), wstring.end());

    return str;
}

static void loadUrlByDefaultBrowser()
{
    // URL 地址
    LPCWSTR url = L"http://localhost:1027";

    // 使用系统默认浏览器打开 URL
    ShellExecuteW(NULL, L"open", url, NULL, NULL, SW_SHOWNORMAL);
}

static std::string createSymlink(const std::string &inputFile)
{
    namespace fs = std::filesystem;

    // Create a symbolic link from "link" to "target"
    fs::path sourcePath(inputFile);
    if (!fs::exists(sourcePath))
        return "";

    // 如果是文件，则获取该文件所在的目录，
    // 然后，创建该目录的软连接到程序的所在目录下的"static/store"目录内
    // 最后，为创建的目录进行静态资源代理
    std::string dirName = "";
    std::string fileName = "";
    if (fs::is_regular_file(sourcePath))
    {
        fileName = sourcePath.filename().string();
        sourcePath = sourcePath.parent_path();
        dirName = sourcePath.filename().string();
    }

    // 即将新建的软连接的路径
    fs::path targetPath = fs::path(STATIC_STORE_DIR + std::string("/") + dirName);

    // 软连接存在，则不重复创建，直接返回uri
    if (fs::is_symlink(targetPath))
    {
        std::cout << "Skip creating symbolic link, because it already exists." << std::endl;
    }
    else
    {
        try
        {
            fs::create_symlink(sourcePath, targetPath);
            std::cout << "Symbolic link created successfully." << std::endl;
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Error creating symbolic link: " << e.what() << std::endl;
            return "";
        }
    }

    //
    std::stringstream uriSs;
    uriSs << "/" << dirName << "/" << fileName;
    return uriSs.str();
}