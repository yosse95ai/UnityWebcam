#include "hedder.h"

OPENCVTEST_API void* getCamera()
{
    // ウィンドウを開く
    return static_cast<void*>(new cv::VideoCapture(0));
}

OPENCVTEST_API void releaseCamera(void* camera)
{
    // ウィンドウを閉じる
    auto vc = static_cast<cv::VideoCapture*>(camera);
    delete vc;
}

OPENCVTEST_API void getCameraTexture(void* camera, unsigned char* data, int width, int height)
{
    auto vc = static_cast<cv::VideoCapture*>(camera);

    // カメラ画の取得
    cv::Mat img;
    *vc >> img;

    // リサイズ
    cv::Mat resized_img(height, width, img.type());
    cv::resize(img, resized_img, resized_img.size(), cv::INTER_CUBIC);


    // RGB --> ARGB 変換
    cv::Mat argb_img;
    cv::cvtColor(resized_img, argb_img, cv::COLOR_RGB2BGRA);
    std::vector<cv::Mat> bgra;
    cv::split(argb_img, bgra);
    std::swap(bgra[0], bgra[3]);
    std::swap(bgra[1], bgra[2]);
    std::memcpy(data, argb_img.data, argb_img.total() * argb_img.elemSize());
}