#include "texture.h"

using namespace ayakaras;

Texture::Texture()
{
    inited = false;
    width = 0;
    height = 0;
}

Texture::Texture(const std::string &name)
{
    image_data = cv::imread(name);
    cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
    width = image_data.cols;
    height = image_data.rows;
    inited = true;
}

Eigen::Vector3f Texture::getColor(float u, float v)
{
    auto u_img = u * width;
    auto v_img = (1 - v) * height;
    auto color = image_data.at<cv::Vec3b>(v_img, u_img);
    return Eigen::Vector3f{color[0], color[1], color[2]};
}