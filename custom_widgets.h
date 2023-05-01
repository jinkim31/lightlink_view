#ifndef CUSTOM_WIDGETS_H
#define CUSTOM_WIDGETS_H

#include <imgui.h>
#include <implot/implot.h>
#include <opencv2/opencv.hpp>

namespace Widget
{
    void setStyle();
    void ImageView(const std::string label, cv::Mat image);
}

#endif