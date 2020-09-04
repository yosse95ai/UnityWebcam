#pragma once
#ifdef UNITYNATIVEPLUGINTEST_EXPORTS
#define UNITYNATIVEPLUGINTEST_API __declspec(dllexport) 
#else
#define UNITYNATIVEPLUGINTEST_API __declspec(dllimport) 
#endif

extern "C"
{
	UNITYNATIVEPLUGINTEST_API void createCheckTexture(unsigned char* arr, int w, int h, int ch);
}