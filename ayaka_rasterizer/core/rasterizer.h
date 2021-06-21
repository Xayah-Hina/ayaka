#ifndef AYAKA_RASTERIZER_RASTERIZER_H
#define AYAKA_RASTERIZER_RASTERIZER_H

#include "model.h"
#include "shader.h"

#include "Eigen/Eigen"

namespace ayakaras
{
    using namespace Eigen;

    struct material
    {
        Vector3f ambient;
        Vector3f diffuse;
        Vector3f specular;
        float shininess;
    };

    enum PRIMITIVE
    {
        LINE, TRIANGLE
    };

    class Rasterizer
    {
    public:
        Rasterizer(unsigned int width, unsigned int height, const Vector3f &CLEAR_COLOR = Vector3f(0.f, 0.f, 0.f));
        void draw(const TriangleModel &m, Shader &vs, PRIMITIVE type = TRIANGLE);
        void clear(bool FRAMEBUFFER, bool DEPTHBUFFER);
    public:
        unsigned int width, height;
        const Vector3f CLEAR_COLOR;
        std::vector<Vector3f> frame_buffer;
        std::vector<float> depth_buffer;
    private:
        void rasterize_triangle(Triangle &t);
        void rasterize_wireframe();
    };
}

#endif //AYAKA_RASTERIZER_RASTERIZER_H
