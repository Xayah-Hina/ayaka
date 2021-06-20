#include "model.h"
#include "utils.h"
#include <iostream>

ayakaras::TriangleModel::TriangleModel(const std::string &filename)
{
    particles = std::make_unique<Particles>();
    mesh = std::make_unique<TriangleFaceMesh>();

    std::vector<Vector3f> positions;
    std::vector<Vector3i> indices;
    std::vector<Vector2f> uvs;

    Utils::loadObj(filename, &positions, &indices, &uvs);

    particles->set_positions(positions);
    particles->set_uvs(uvs);
    mesh->load_faces(indices);

    if (!setup(filename))
    {
        std::cerr << "Fail to load" << filename << std::endl;
    }
}

bool ayakaras::TriangleModel::setup(const std::string &filename)
{
    std::vector<Vector3f> vertices;
    std::vector<Vector3i> indicies;
    if (!Utils::loadObj(filename, &vertices, &indicies))
        return false;
    this->particles->load_vertices(vertices);
    this->mesh->load_faces(indicies);
    return true;
}

const ayakaras::Particles &ayakaras::TriangleModel::get_particles() const
{
    return *particles;
}

const ayakaras::TriangleFaceMesh &ayakaras::TriangleModel::get_mesh() const
{
    return *mesh;
}