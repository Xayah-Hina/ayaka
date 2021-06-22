#include "triangle.h"

#include <assert.h>

#include <utility>

using namespace ayakaras;

Triangle::Triangle(const Particles &p, unsigned int a, unsigned int b, unsigned int c, const Material *_mat)
{
    positions[0] = p.get_positions()[a];
    positions[1] = p.get_positions()[b];
    positions[2] = p.get_positions()[c];
    positions_viewed[0] = p.get_positions()[a];
    positions_viewed[1] = p.get_positions()[b];
    positions_viewed[2] = p.get_positions()[c];
    positions_projected[0] = p.get_positions()[a];
    positions_projected[1] = p.get_positions()[b];
    positions_projected[2] = p.get_positions()[c];
    normals[0] = p.get_normals()[a];
    normals[1] = p.get_normals()[b];
    normals[2] = p.get_normals()[c];
    uvs[0] = p.get_uvs()[a];
    uvs[1] = p.get_uvs()[b];
    uvs[2] = p.get_uvs()[c];
    mat = _mat;
}

const Vector3f *Triangle::get_positions_projected() const
{
    return positions_projected;
}

const Vector3f *Triangle::get_positions_viewed() const
{
    return positions_viewed;
}

const Vector3f *Triangle::get_positions() const
{
    return positions;
}

const Vector3f *Triangle::get_normals() const
{
    return normals;
}

const Vector2f *Triangle::get_uvs() const
{
    return uvs;
}

const Vector3f *Triangle::get_tangents() const
{
    return tangents;
}

const Vector3f *Triangle::get_bitangents() const
{
    return bitangents;
}

const Vector3f *Triangle::get_colors() const
{
    return colors;
}

const Material *Triangle::get_mat() const
{
    return mat;
}


void Triangle::set_position_projected(unsigned int i, Vector3f p)
{
    assert(i <= 3);
    Triangle::positions_projected[i] = std::move(p);
}

void Triangle::set_position_viewed(unsigned int i, Vector3f p)
{
    assert(i <= 3);
    Triangle::positions_viewed[i] = std::move(p);
}

void Triangle::set_position(unsigned int i, Vector3f p)
{
    assert(i <= 3);
    Triangle::positions[i] = std::move(p);
}

void Triangle::set_normal(unsigned int i, Vector3f n)
{
    assert(i <= 3);
    Triangle::normals[i] = std::move(n);
}

void Triangle::set_uv(unsigned int i, Vector2f uv)
{
    assert(i <= 3);
    Triangle::uvs[i] = std::move(uv);
}

void Triangle::set_tangent(unsigned int i, Vector3f t)
{
    assert(i <= 3);
    Triangle::tangents[i] = std::move(t);
}

void Triangle::set_bitangent(unsigned int i, Vector3f b)
{
    assert(i <= 3);
    Triangle::bitangents[i] = std::move(b);
}

void Triangle::set_color(unsigned int i, Vector3f c)
{
    assert(i <= 3);
    Triangle::colors[i] = std::move(c);
}