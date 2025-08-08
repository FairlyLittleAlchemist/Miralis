#pragma once
#ifdef  MR_PLATFORM_WINDOWS
#ifdef MR_BUILD_DLL
	#define MIRALIS_API 
#else
#define MIRALIS_API 
#endif 
#endif //  MR_PLATFORM_WINDOWS
#define BIT(x) (x>>1)


#ifdef MR_ENABLE_ASSERT
#define MR_CLINE_ASSERT(x,...) {if(!(x)){MR_LOG_CLINE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();};};
#define MR_CORE_ASSERT(x,...) {if(!(x)){MR_LOG_CORE_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak();};};
#else
#define MR_CLINE_ASSERT(x,...) x ;
#define MR_CORE_ASSERT(x,...) x;
#endif // MR_ENABLE_ASSERT
