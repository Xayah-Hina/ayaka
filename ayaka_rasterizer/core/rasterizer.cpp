#include "rasterizer.h"
#include "triangle.h"

#include <iostream>

using namespace ayakaras;

std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Triangle &t)
{
    Eigen::Vector3f P(x, y, 0);

    Eigen::Vector3f AB = t.get_positions_projected()[1] - t.get_positions_projected()[0];
    Eigen::Vector3f BC = t.get_positions_projected()[2] - t.get_positions_projected()[1];
    Eigen::Vector3f CA = t.get_positions_projected()[0] - t.get_positions_projected()[2];

    AB[2] = 0;
    BC[2] = 0;
    CA[2] = 0;

    Eigen::Vector3f PA = t.get_positions_projected()[0] - P;
    Eigen::Vector3f PB = t.get_positions_projected()[1] - P;
    Eigen::Vector3f PC = t.get_positions_projected()[2] - P;

    float alpha = PB.cross(PC).z() / AB.cross(BC).z();
    float beta = PC.cross(PA).z() / AB.cross(BC).z();
    float gamma = PA.cross(PB).z() / AB.cross(BC).z();

    return {alpha, beta, gamma};
}

void Rasterizer::set_pixel(unsigned int x, unsigned int y, const Vector3f &color)
{
    unsigned int ind = (height - 1 - y) * width + x;
    this->frame_buffer[ind] = color;
}

void Rasterizer::set_depth(unsigned int x, unsigned int y, float depth)
{
    unsigned int ind = (height - 1 - y) * width + x;
    this->depth_buffer[ind] = depth;
}

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

    TriangleFaceMesh::Faces faces = tm.get_faces();
    if (faces.size() % 3)
    {
        std::cerr << "RASTERIZING ERROR:: FACE NUM ERROR" << std::endl;
        return;
    }
    for (unsigned int i = 0; i < faces.size(); i += 3)
    {

        Triangle tri(p, faces[i], faces[i + 1], faces[i + 2]);

        shader.shade_vertex(tri, Rasterizer::width, Rasterizer::height);

        if (type == LINE)
            rasterize_wireframe(tri);
        else if (type == TRIANGLE)
            rasterize_triangle(tri);
    }
}

void ayakaras::Rasterizer::clear(bool FRAMEBUFFER, bool DEPTHBUFFER)
{
    if (FRAMEBUFFER)
        std::fill(this->frame_buffer.begin(), this->frame_buffer.end(), CLEAR_COLOR);
    if (DEPTHBUFFER)
        std::fill(this->depth_buffer.begin(), this->depth_buffer.end(), -std::numeric_limits<float>::infinity());
}

void Rasterizer::rasterize_triangle(const Triangle &t)
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

    for (int i = left; i <= right; ++i)
    {
        for (int j = bottom; j <= top; ++j)
        {
            if (i < 0 || i >= width || j < 0 || j >= height)
                continue;
            auto[alpha, beta, gamma] = computeBarycentric2D((float) i, (float) j, t);
            if (alpha >= 0 && beta >= 0 && gamma >= 0)
            {
                // ============================== DEPTH TEST ==============================
                const Vector3f &a_view = t.get_positions_viewed()[0];
                const Vector3f &b_view = t.get_positions_viewed()[1];
                const Vector3f &c_view = t.get_positions_viewed()[2];
                float z_interpolated_view = 1 / (alpha / a_view.z() + beta / b_view.z() + gamma / c_view.z());
                float depth_interpolated = z_interpolated_view * (alpha * a.z() / a_view.z() + beta * b.z() / b_view.z() + gamma * c.z() / c_view.z());
                if (depth_interpolated > depth_buffer[(height - 1 - j) * width + i])
                {
                    Vector3f color_interpolated{250, 250, 250};
                    set_pixel(i, j, color_interpolated);
                    set_depth(i, j, depth_interpolated);
                }
            }
        }
    }
}

void Rasterizer::rasterize_wireframe(const Triangle &t)
{
    const Vector3f &a = t.get_positions_projected()[0];
    const Vector3f &b = t.get_positions_projected()[1];
    const Vector3f &c = t.get_positions_projected()[2];
    draw_line(a, b);
    draw_line(b, c);
    draw_line(c, a);
}

void Rasterizer::draw_line(Vector3f begin, Vector3f end)
{
    // Bresenham Algorithm
    auto x1 = begin.x();
    auto y1 = begin.y();
    auto x2 = end.x();
    auto y2 = end.y();

    Eigen::Vector3f line_color = {255, 255, 255};

    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

    dx = static_cast<int>(x2 - x1);
    dy = static_cast<int>(y2 - y1);
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;

    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        } else
        {
            x = x2;
            y = y2;
            xe = x1;
        }
        set_pixel(x, y, line_color);
        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
            {
                px = px + 2 * dy1;
            } else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    y = y + 1;
                } else
                {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }
            set_pixel(x, y, line_color);
        }
    } else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        } else
        {
            x = x2;
            y = y2;
            ye = y1;
        }
        set_pixel(x, y, line_color);
        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
            {
                py = py + 2 * dx1;
            } else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    x = x + 1;
                } else
                {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }
            set_pixel(x, y, line_color);
        }
    }
}