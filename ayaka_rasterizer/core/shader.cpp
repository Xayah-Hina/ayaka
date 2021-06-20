#include "shader.h"

#include <array>

using namespace ayakaras;

Eigen::Vector4f to_vec4(const Eigen::Vector3f &v3, float w = 1.0f)
{
    return {Eigen::Vector4f(v3.x(), v3.y(), v3.z(), w)};
}

bool Shader::shade(Triangle &t, std::vector<Vector3f> &frame_buf, std::vector<float> &depth_buf, unsigned int width, unsigned height)
{
    Matrix4f mvp = projection * view * model;
    Matrix4f inv_trans = (view * model).inverse().transpose();
    for (unsigned int i = 0; i < 3; ++i)
    {
        Vector4f tp = mvp * Vector4f(t.get_positions()[i].x(), t.get_positions()[i].y(), t.get_positions()[i].z(), 1.f);
        Vector4f tn = inv_trans * Vector4f(t.get_normals()[i].x(), t.get_normals()[i].y(), t.get_normals()[i].z(), 1.f);

        tp /= tp.z();

        t.set_position(i, tp.head<3>());
        t.set_normal(i, tn.head<3>());
    }
    return true;
}