#pragma once

#if defined(BUILDING_API_DLL)  
    #define API_DLL_EXPORT __declspec(dllexport)  
#else  
    #define API_DLL_EXPORT __declspec(dllimport)  
#endif  
  
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
    extern "C" {
#endif
        API_DLL_EXPORT void sayHello();

        API_DLL_EXPORT uint8_t startServer(uint16_t port);

        API_DLL_EXPORT uint8_t stopServer();
#ifdef __cplusplus
    };
#endif
