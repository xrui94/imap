cmake_minimum_required(VERSION 3.21)

set(PROJECT_NAME imap)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME})

option(SHARED "Compile the program as a dynamic library." ON)

if (MSVC)
    add_compile_options(/wd4819)    #忽略保存为unicode警告

    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

#设置输出目录
if (CMAKE_BUILD_TYPE)
    string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
    
    if (${BUILD_TYPE} STREQUAL "debug")
        set(CMAKE_BUILD_TYPE "Debug")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
    elseif (${BUILD_TYPE} STREQUAL "release")
        set(CMAKE_BUILD_TYPE "Release")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3")
    else()
        set(CMAKE_BUILD_TYPE "Debug")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
    endif()
else()
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
endif()

message(STATUS "${PROJECT_NAME} CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")

# 自定义变量，设置三方库的路径
# set(THIRD_PARTY_DIR C:/env/libc++)

# 设置头文件搜索目录
include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/thirdParty
)

# 设置需要编译的源文件
file(GLOB_RECURSE SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

## 编译入口程序
if(SHARED)
    add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
else()
    add_executable(${PROJECT_NAME} ${SRC_FILES})
endif(SHARED)

#
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    # In dev mode, we load static from the source tree, so that when we
    # dynamically edit static (like shaders), these are correctly
    # versionned.
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        STATIC_DIR="../${CMAKE_CURRENT_SOURCE_DIR}/dist"
    )
else()
    # In release mode, we just load static relatively to wherever the
    # executable is launched from, so that the binary is portable
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        STATIC_DIR="./static"
    )
endif()

#
# target_link_libraries(${PROJECT_NAME} user32)

# 指定 /SUBSYSTEM:WINDOWS 选项，告诉链接器生成一个 Windows 窗口程序
# 默认为：/SUBSYSTEM:CONSOLE，即控制台程序
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")