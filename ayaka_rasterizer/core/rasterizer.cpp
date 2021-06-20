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

void Rasterizer::draw(const TriangleModel &m, Shader &shader, const PRIMITIVE type) const
{
    const Particles &p = m.get_particles();
    const TriangleFaceMesh &tm = m.get_mesh();

    if (type == TRIANGLE)
    {
        TriangleFaceMesh::Faces faces = tm.get_faces();
        if (!(faces.size() % 3))
        {
            std::cerr << "RASTERIZING ERROR:: FACE NUM ERROR" << std::endl;
        }
        for (unsigned int i = 0; i < faces.size(); i += 3)
        {
            const Vector3f &a = p.get_vertice(i);
            const Vector3f &b = p.get_vertice(i + 1);
            const Vector3f &c = p.get_vertice(i + 2);

            std::vector<Vector3f> triangle{a, b, c};

            Triangle tri(p, i, i + 1, i + 2);

            std::vector<Vector3f> frame_buf;
            std::vector<float> depth_buf;

            shader.shade(tri, frame_buf, depth_buf, Rasterizer::width, Rasterizer::height);

            for (unsigned int j = 0; j < 3; ++j)
            {
                Vector3f tp = tri.get_positions()[j];
                tp.x() = 0.5 * width * (tp.x() + 1.0);
                tp.y() = 0.5 * height * (tp.y() + 1.0);
                tp.z() = tp.z() * (49.9f / 2.f) + (50.1f / 2.f);
                tri.set_position(j, tp);
            }

            int left = std::floor(std::min({a.x(), b.x(), c.x()}));
            int right = std::floor(std::max({a.x(), b.x(), c.x()}));
            int bottom = std::floor(std::min({a.y(), b.y(), c.y()}));
            int top = std::floor(std::max({a.y(), b.y(), c.y()}));

            if (top < 0 || right < 0 || bottom > height || left > width)
                continue;// clip triangle

            for (int j = left; j <= right; ++j)
            {
                for (int k = bottom; k < top; ++k)
                {
                    if (j < 0 || j >= width || k < 0 || k >= height)
                        continue;

                }
            }
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

void Rasterizer::rasterize_triangle()
{

}

void Rasterizer::rasterize_wireframe()
{

}