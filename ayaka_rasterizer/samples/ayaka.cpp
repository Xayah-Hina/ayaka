#include "model.h"
#include "rasterizer.h"

using namespace std;
using namespace Eigen;

unsigned int width = 800;
unsigned int height = 600;

int main(int argc, char **argv)
{
    std::unique_ptr<ayakaras::TriangleModel> model = std::make_unique<ayakaras::TriangleModel>("cube.obj");

    ayakaras::Rasterizer rst(width, height);

    rst.draw(*model);
}