#ifndef AYAKA_RASTERIZER_SHADER_H
#define AYAKA_RASTERIZER_SHADER_H

#include "triangle.h"

#include "Eigen/Eigen"

#include <vector>

namespace ayakaras
{
    using namespace Eigen;

    class Shader
    {
    public:
        virtual bool shade(Triangle &t, std::vector<Vector3f> &frame_buf, std::vector<float> &depth_buf, unsigned int width, unsigned height);

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
