#ifndef AYAKA_RASTERIZER_TRIANGLE_H
#define AYAKA_RASTERIZER_TRIANGLE_H

#include "particles.h"

#include <Eigen/Eigen>
#include <vector>

namespace ayakaras
{
    using namespace Eigen;

    class Triangle
    {
    public:
        Triangle(const Particles &p, unsigned int a, unsigned int b, unsigned int c);

        const Vector3f *get_positions_projected() const;
        const Vector3f *get_positions() const;
        const Vector3f *get_normals() const;
        const Vector2f *get_uvs() const;
        const Vector3f *get_tangents() const;
        const Vector3f *get_bitangents() const;
        const Vector3f *get_colors() const;

        void set_position_projected(unsigned int i, Vector3f p);
        void set_position(unsigned int i, Vector3f p);
        void set_normal(unsigned int i, Vector3f n);
        void set_uv(unsigned int i, Vector2f uv);
        void set_tangent(unsigned int i, Vector3f t);
        void set_bitangent(unsigned int i, Vector3f b);
        void set_color(unsigned int i, Vector3f c);

    protected:
        Vector3f positions_projected[3];
        Vector3f positions[3];
        Vector3f normals[3];
        Vector2f uvs[3];
        Vector3f tangents[3];
        Vector3f bitangents[3];
        Vector3f colors[3];
    };
}

#endif //AYAKA_RASTERIZER_TRIANGLE_H
