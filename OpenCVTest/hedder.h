#pragma once
#include <opencv2/opencv.hpp>

#ifdef OPENCVTEST_EXPORTS
#define OPENCVTEST_API __declspec(dllexport) 
#else
#define OPENCVTEST_API __declspec(dllimport)
#endif

extern "C" {
    OPENCVTEST_API void* getCamera();
    OPENCVTEST_API void releaseCamera(void* camera);
    OPENCVTEST_API void getCameraTexture(void* camera, unsigned char* data, int width, int height);
}