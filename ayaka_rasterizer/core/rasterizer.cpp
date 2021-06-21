#include "rasterizer.h"
#include "triangle.h"

#include <iostream>

using namespace ayakaras;

Rasterizer::Rasterizer(unsigned int width, unsigned int height, const Vector3f &CLEAR_COLOR) : CLEAR_COLOR(CLEAR_COLOR)
{
    Rasterizer::width = width;
    Rasterizer::height = height;
    frame_buffer.resize(width * height, CLEAR_COLOR);
    depth_buffer.resize(width * height, -std::numeric_limits<float>::infinity());
}

void Rasterizer::draw(const TriangleModel &m, Shader &shader, const PRIMITIVE type)
{
    const Particles &p = m.get_particles()[0];
    const TriangleFaceMesh &tm = m.get_meshes()[0];

    if (type == TRIANGLE)
    {
        TriangleFaceMesh::Faces faces = tm.get_faces();
        if (!(faces.size() % 3))
        {
            std::cerr << "RASTERIZING ERROR:: FACE NUM ERROR" << std::endl;
        }
        for (unsigned int i = 0; i < faces.size(); i += 3)
        {

            Triangle tri(p, faces[i], faces[i + 1], faces[i + 2]);

            std::vector<Vector3f> frame_buf;
            std::vector<float> depth_buf;

            shader.shade_vertex(tri, frame_buf, depth_buf, Rasterizer::width, Rasterizer::height);

            rasterize_triangle(tri);

        }
    }
}

void ayakaras::Rasterizer::clear(bool FRAMEBUFFER, bool DEPTHBUFFER)
{
    if (FRAMEBUFFER)
        std::fill(this->frame_buffer.begin(), this->frame_buffer.end(), CLEAR_COLOR);
    if (DEPTHBUFFER)
        std::fill(this->depth_buffer.begin(), this->depth_buffer.end(), -std::numeric_limits<float>::infinity());
}

void Rasterizer::rasterize_triangle(Triangle &t)
{
    const Vector3f &a = t.get_positions_projected()[0];
    const Vector3f &b = t.get_positions_projected()[1];
    const Vector3f &c = t.get_positions_projected()[2];

    int left = std::floor(std::min({a.x(), b.x(), c.x()}));
    int right = std::floor(std::max({a.x(), b.x(), c.x()}));
    int bottom = std::floor(std::min({a.y(), b.y(), c.y()}));
    int top = std::floor(std::max({a.y(), b.y(), c.y()}));

    if (top < 0 || right < 0 || bottom > height || left > width)
        return;// clip triangle

    for (int j = left; j <= right; ++j)
    {
        for (int k = bottom; k < top; ++k)
        {
            if (j < 0 || j >= width || k < 0 || k >= height)
                continue;

        }
    }
}

void Rasterizer::rasterize_wireframe()
{

}