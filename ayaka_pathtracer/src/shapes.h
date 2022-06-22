#ifndef AYAKAPATHTRACER_SHAPES_H
#define AYAKAPATHTRACER_SHAPES_H

#include <optional>

/**
 * @brief The ShapeT class
 * @tparam Vector3
 * NEED TO BE IMPLEMENTED:
 *  1. Vector3::dot(Vector3)
 */

template<typename Vector3>
struct hit_recordT
{
    Vector3 p;
    Vector3 normal;
    float t;
    bool front_face;
};

template<typename Vector3>
struct ShapeT
{
    virtual std::optional<hit_recordT<Vector3>> intersect(const Vector3 &orig, const Vector3 &dir, float t_min, float t_max) = 0;
};

template<typename Vector3>
struct SphereT : public ShapeT<Vector3>
{
    SphereT(const Vector3 &center, float radius);
    std::optional<hit_recordT<Vector3>> intersect(const Vector3 &orig, const Vector3 &dir, float t_min, float t_max) override;

    Vector3 _center;
    float _radius;
};

template<typename Vector3>
SphereT<Vector3>::SphereT(const Vector3 &center, float radius) : _center(center), _radius(radius)
{}

template<typename Vector3>
std::optional<hit_recordT<Vector3>> SphereT<Vector3>::intersect(const Vector3 &orig, const Vector3 &dir, float t_min, float t_max)
{
    Vector3 oc = orig - _center;
    auto a = 1;
    auto hb = oc.dot(dir);
    auto c = oc.dot(oc) - _radius * _radius;
    auto discriminant = hb * hb - a * c;

    if (discriminant < 0)
        return std::nullopt;

    auto t = -hb - std::sqrt(discriminant);

    if (t < t_min || t > t_max)
        return std::nullopt;

    auto p = orig + dir * t;
    auto n = (p - _center).normalized();

    if (dir.dot(n) < 0)
        return {{p, n, t, true}};

    n = -n;
    return {{p, n, t, false}};

}

#endif //AYAKAPATHTRACER_SHAPES_H
