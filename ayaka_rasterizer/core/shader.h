#ifndef AYAKA_RASTERIZER_SHADER_H
#define AYAKA_RASTERIZER_SHADER_H

#include "triangle.h"
#include "texture.h"

#include "Eigen/Eigen"

#include <vector>

namespace ayakaras
{
    using namespace Eigen;

    class Shader
    {
    public:
        struct PointLight
        {
            Vector3f position;
            float constant;
            float linear;
            float quadratic;
            Vector3f ambient;
            Vector3f diffuse;
            Vector3f specular;
        };
    public:
        virtual bool shade_vertex(Triangle &t, std::vector<Vector3f> &frame_buf, std::vector<float> &depth_buf, unsigned int width, unsigned height);

        virtual bool shade_fragment();

        virtual void set_mvp(Matrix4f m, Matrix4f v, Matrix4f p) final
        {
            model = m;
            view = v;
            projection = p;
        }

    protected:
        Matrix4f model, view, projection;
    };
}

#endif //AYAKA_RASTERIZER_SHADER_H
