#ifndef AYAKA_RASTERIZER_TRIANGLE_H
#define AYAKA_RASTERIZER_TRIANGLE_H

#include "particles.h"
#include "material.h"

#include <Eigen/Eigen>
#include <vector>

namespace ayakaras
{
    using namespace Eigen;

    class Triangle
    {
    public:
        Triangle(const Particles &p, unsigned int a, unsigned int b, unsigned int c, unsigned int ua, unsigned int ub, unsigned int uc, unsigned int na, unsigned int nb, unsigned int nc, const Material *_mat = nullptr);

        [[nodiscard]] const Vector3f *get_positions_projected() const;
        [[nodiscard]] const Vector3f *get_positions_viewed() const;
        [[nodiscard]] const Vector3f *get_positions() const;
        [[nodiscard]] const Vector3f *get_normals() const;
        [[nodiscard]] const Vector2f *get_uvs() const;
        [[nodiscard]] const Vector3f *get_tangents() const;
        [[nodiscard]] const Vector3f *get_bitangents() const;
        [[nodiscard]] const Vector3f *get_colors() const;
        [[nodiscard]] const Material *get_mat() const;

        void set_position_projected(unsigned int i, Vector3f p);
        void set_position_viewed(unsigned int i, Vector3f p);
        void set_position(unsigned int i, Vector3f p);
        void set_normal(unsigned int i, Vector3f n);
        void set_uv(unsigned int i, Vector2f uv);
        void set_tangent(unsigned int i, Vector3f t);
        void set_bitangent(unsigned int i, Vector3f b);
        void set_color(unsigned int i, Vector3f c);

    protected:
        Vector3f positions_projected[3];
        Vector3f positions_viewed[3];
        Vector3f positions[3];
        Vector3f normals[3];
        Vector2f uvs[3];
        Vector3f tangents[3];
        Vector3f bitangents[3];
        Vector3f colors[3];
        const Material *mat;
    };
}

#endif //AYAKA_RASTERIZER_TRIANGLE_H
