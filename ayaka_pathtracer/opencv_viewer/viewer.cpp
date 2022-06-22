#include "viewer.h"

void Viewer::display_one_frame(void *buffer, int width, int height)
{
    cv::Mat image(height, width, CV_32FC3, buffer);
    cv::Mat image_bgr;
    cv::cvtColor(image, image_bgr, cv::COLOR_RGB2BGR);
    cv::imshow("OpenCV Viewer", image_bgr);
    cv::waitKey(0);
}
