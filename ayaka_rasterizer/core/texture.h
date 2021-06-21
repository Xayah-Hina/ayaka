#ifndef AYAKA_RASTERIZER_TEXTURE_H
#define AYAKA_RASTERIZER_TEXTURE_H

#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

namespace ayakaras
{
    class Texture
    {
    public:
        Texture();

        explicit Texture(const std::string &name);

        Eigen::Vector3f getColor(float u, float v);

    private:
        bool inited;
        int width, height;
        cv::Mat image_data;
    };
}

#endif //AYAKA_RASTERIZER_TEXTURE_H
