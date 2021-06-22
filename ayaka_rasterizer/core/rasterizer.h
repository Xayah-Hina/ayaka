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
        Rasterizer(unsigned int width, unsigned int height, const Vector3f &CLEAR_COLOR = Vector3f{253.f, 237.f, 228.f});
        void draw(const TriangleModel &m, Shader &vs, PRIMITIVE type = TRIANGLE);
        void clear(bool FRAMEBUFFER, bool DEPTHBUFFER);
    public:
        unsigned int width, height;
        const Vector3f CLEAR_COLOR;
        std::vector<Vector3f> frame_buffer;
        std::vector<float> depth_buffer;
        std::vector<Vector3f> geometry_buffer;
    private:
        void rasterize_triangle(const Triangle &t, Shader &shader);
        void rasterize_wireframe(const Triangle &t, Shader &shader);
        void draw_line(Vector3f begin, Vector3f end);
        void set_pixel(unsigned int x, unsigned int y, const Vector3f &color);
        void set_depth(unsigned int x, unsigned int y, float depth);
    };
}

#endif //AYAKA_RASTERIZER_RASTERIZER_H
