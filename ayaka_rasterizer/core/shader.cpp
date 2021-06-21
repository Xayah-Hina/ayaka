#include "shader.h"

#include <array>

using namespace ayakaras;

Eigen::Vector4f to_vec4(const Eigen::Vector3f &v3, float w = 1.0f)
{
    return Eigen::Vector4f{v3.x(), v3.y(), v3.z(), w};
}

bool Shader::shade_vertex(Triangle &t, unsigned int width, unsigned int height)
{
    Matrix4f inv_trans = (view * model).inverse().transpose();
    for (unsigned int i = 0; i < 3; ++i)
    {
        Vector4f tm = model * Vector4f(t.get_positions()[i].x(), t.get_positions()[i].y(), t.get_positions()[i].z(), 1.f);
        Vector4f tv = view * model * Vector4f(t.get_positions()[i].x(), t.get_positions()[i].y(), t.get_positions()[i].z(), 1.f);
        Vector4f tp = projection * view * model * Vector4f(t.get_positions()[i].x(), t.get_positions()[i].y(), t.get_positions()[i].z(), 1.f);
        Vector4f tn = inv_trans * Vector4f(t.get_normals()[i].x(), t.get_normals()[i].y(), t.get_normals()[i].z(), 0.f);

        tm /= tm.w();
        tv /= tm.w();
        tp /= tp.w();

        tp.x() = 0.5 * width * (tp.x() + 1.0);
        tp.y() = 0.5 * height * (tp.y() + 1.0);
        tp.z() = tp.z() * (49.9f / 2.f) + (50.1f / 2.f);

        t.set_position(i, tm.head<3>());
        t.set_position_viewed(i, tv.head<3>());
        t.set_position_projected(i, tp.head<3>());
        t.set_normal(i, tn.head<3>());
    }
    return true;
}

bool Shader::shade_fragment()
{
    return true;
}
