#pragma once
#ifdef  MR_PLATFORM_WINDOWS
#ifdef MR_BUILD_DLL
#define MIRALIS_API _declspec(dllexport)
#else
#define MIRALIS_API _declspec(dllimport)
#endif 
#endif //  MR_PLATFORM_WINDOWS
