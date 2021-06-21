#ifndef AYAKA_RASTERIZER_PARTICLES_H
#define AYAKA_RASTERIZER_PARTICLES_H

#include <vector>
#include <Eigen/Eigen>

namespace ayakaras
{
    using namespace Eigen;

    class Particles
    {
    public:

        const Vector3f &get_vertice(unsigned int i) const
        {
            assert(i >= 1 && i <= positions.size());
            return positions[i];
        }

        void load_vertices(std::vector<Vector3f> &vertices)
        {
            size_t num = vertices.size();
            positions.reserve(num);
            for (int i = 0; i < num; ++i)
                positions.push_back(vertices[i]);
        }

        const std::vector<Vector3f> &get_positions() const
        {
            return positions;
        }

        const std::vector<Vector3f> &get_normals() const
        {
            return normals;
        }

        const std::vector<Vector2f> &get_uvs() const
        {
            return uvs;
        }

        const std::vector<Vector3f> &get_tangent() const
        {
            return tangent;
        }

        const std::vector<Vector3f> &get_bitangent() const
        {
            return bitangent;
        }

        void set_positions(const std::vector<Vector3f> &_positions)
        {
            Particles::positions = _positions;
        }

        void set_normals(const std::vector<Vector3f> &_normals)
        {
            Particles::normals = _normals;
        }

        void set_uvs(const std::vector<Vector2f> &_uvs)
        {
            Particles::uvs = _uvs;
        }

        void set_tangent(const std::vector<Vector3f> &_tangent)
        {
            Particles::tangent = _tangent;
        }

        void set_bitangent(const std::vector<Vector3f> &_bitangent)
        {
            Particles::bitangent = _bitangent;
        }

    protected:
        std::vector<Vector3f> positions;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;
        std::vector<Vector3f> tangent;
        std::vector<Vector3f> bitangent;
        std::vector<Vector3f> colors;
    };
}

#endif //AYAKA_RASTERIZER_PARTICLES_H
