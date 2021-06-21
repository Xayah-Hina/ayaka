#include "model.h"
#include "utils.h"
#include <iostream>

using namespace ayakaras;

TriangleModel::TriangleModel(const std::string &filename)
{
    if (!setup(filename))
        std::cerr << "Fail to load " << filename << std::endl;
}

bool TriangleModel::setup(const std::string &filename)
{
    Particles p;
    TriangleFaceMesh tfm;

    std::vector<Vector3f> positions;
    std::vector<Vector3f> normals;
    std::vector<Vector3i> indices;
    std::vector<Vector2f> uvs;
    Material mat;

    mat.diffuse = Texture("/Users/polaris/Desktop/tetwildsample/willowTreeBranch_v1_L2.123ceab7b7ac-6102-4fab-8f06-392a891b5ebd/12972_willowTreeBranch_diffuse.jpg");

    if (!(Utils::loadObj(filename, &positions, &indices, &uvs, &normals)))
        return false;

    p.set_positions(positions);
    p.set_normals(normals);
    p.set_uvs(uvs);
    tfm.load_faces(indices);

    particles.push_back(std::move(p));
    meshes.push_back(std::move(tfm));
    materials.push_back(std::move(mat));
    return true;
}

const std::vector<Particles> &TriangleModel::get_particles() const
{
    return particles;
}

const std::vector<TriangleFaceMesh> &TriangleModel::get_meshes() const
{
    return meshes;
}

const std::vector<Material> &TriangleModel::get_materials() const
{
    return materials;
}

const unsigned int TriangleModel::get_meshsize() const
{
    assert(particles.size() == meshes.size());
    return static_cast<unsigned int>(particles.size());
}