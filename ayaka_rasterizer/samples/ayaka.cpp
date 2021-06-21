#include "model.h"
#include "rasterizer.h"
#include "shader.h"
#include "camera.h"

#include "opencv2/opencv.hpp"

using namespace std;
using namespace Eigen;

unsigned int width = 800;
unsigned int height = 800;

int main(int argc, char **argv)
{
    ayakaras::Rasterizer rst(width, height);

    std::unique_ptr<ayakaras::TriangleModel> model = std::make_unique<ayakaras::TriangleModel>("branch.obj");

    ayakaras::Shader shader;

    ayakaras::Camera camera;
    shader.set_mvp(camera.get_model_matrix(0, 0, 0), camera.get_view_matrix(), camera.get_projection_matrix(45, height / width, -0.1, -50));

    rst.draw(*model, shader, ayakaras::TRIANGLE);

    cv::Mat image(height, width, CV_32FC3, rst.frame_buffer.data());

    image.convertTo(image, CV_8UC3, 1.0f);

    cv::imwrite("/Users/polaris/Desktop/tetwildsample/willowTreeBranch_v1_L2.123ceab7b7ac-6102-4fab-8f06-392a891b5ebd/test.png", image);
}
