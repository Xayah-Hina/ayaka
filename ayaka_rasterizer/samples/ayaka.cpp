#include "model.h"
#include "rasterizer.h"
#include "shader.h"
#include "camera.h"

using namespace std;
using namespace Eigen;

unsigned int width = 800;
unsigned int height = 800;

int main(int argc, char **argv)
{
    ayakaras::Rasterizer rst(width, height);

    std::unique_ptr<ayakaras::TriangleModel> model = std::make_unique<ayakaras::TriangleModel>("cube.obj");

    ayakaras::Shader shader;

    ayakaras::Camera camera;
    shader.set_mvp(camera.get_model_matrix(0, 0, 0), camera.get_view_matrix(), camera.get_projection_matrix(45, height / width, -0.1, -50));

    rst.draw(*model, shader, ayakaras::TRIANGLE);
}
