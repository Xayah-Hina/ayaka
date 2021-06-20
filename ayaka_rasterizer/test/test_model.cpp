#include "utils.h"

#include "Eigen/Eigen"

using namespace Eigen;

int main()
{
    std::clog << "==================== START TEST model.h ====================" << std::endl;
    std::vector<Vector3f> positions;
    std::vector<Vector3i> indicies;
    assert(Utils::loadObj("sphere.obj", &positions, &indicies));
    std::clog << "==================== ayakaras::TriangleModel::loadObj() PASSED ====================" << std::endl;
}