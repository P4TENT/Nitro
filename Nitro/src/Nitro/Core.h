#pragma once

#ifdef NG_PLATFORM_WINDOWS
	#ifdef NG_BUILD_DLL
		#define NITRO_API __declspec(dllexport)
	#else 
		#define NITRO_API __declspec(dllimport)
	#endif
#else 
	#error Nitro only supports Windows!!
#endif