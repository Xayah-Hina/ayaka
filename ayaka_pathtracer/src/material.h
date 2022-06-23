#ifndef AYAKAPATHTRACER_MATERIAL_H
#define AYAKAPATHTRACER_MATERIAL_H

template<typename Vector3>
static Vector3 random_in_unit_sphere()
{
    auto length = Random::random_f(0.0f, 1.0f);
    auto angle = Random::random_f(0.0f, 2.0f * 3.141592654f);
    auto theta = Random::random_f(0.0f, 2.0f * 3.141592654f);
    return {length * std::cos(theta) * std::cos(angle), length * std::cos(theta) * std::sin(angle), length * std::sin(theta)};
}

template<typename Vector3>
bool near_zero(const Vector3 &v)
{
    return std::abs(v.x()) < 1e-6 && std::abs(v.y()) < 1e-6 && std::abs(v.z()) < 1e-6;
}

template<typename Vector3>
Vector3 reflect(const Vector3 &v, const Vector3 &n)
{
    return v - 2.0f * v.dot(n) * n;
}

template<typename Vector3, typename Ray>
struct MaterialT
{
    virtual bool scatter(const Ray &r_in, const Vector3 &hit_point, const Vector3 &hit_normal, Vector3 &attenuation, Ray &scattered) const = 0;
};

template<typename Vector3, typename Ray>
struct LambertianT : public MaterialT<Vector3, Ray>
{
    explicit LambertianT(const Vector3 &albedo);
    bool scatter(const Ray &r_in, const Vector3 &hit_point, const Vector3 &hit_normal, Vector3 &attenuation, Ray &scattered) const override;

    Vector3 _albedo;
};

template<typename Vector3, typename Ray>
LambertianT<Vector3, Ray>::LambertianT(const Vector3 &albedo) : _albedo(albedo)
{}

template<typename Vector3, typename Ray>
bool LambertianT<Vector3, Ray>::scatter(const Ray &r_in, const Vector3 &hit_point, const Vector3 &hit_normal, Vector3 &attenuation, Ray &scattered) const
{
    Vector3 scatter_direction = (hit_normal + random_in_unit_sphere<Vector3>().normalized()).normalized();

    if (near_zero<Vector3>(scatter_direction))
        scatter_direction = hit_normal.normalized();

    scattered = Ray(hit_point, scatter_direction);
    attenuation = _albedo;
    return true;
}

template<typename Vector3, typename Ray>
struct MetalT : public MaterialT<Vector3, Ray>
{
    explicit MetalT(const Vector3 &albedo, float fuzz);
    bool scatter(const Ray &r_in, const Vector3 &hit_point, const Vector3 &hit_normal, Vector3 &attenuation, Ray &scattered) const override;

    Vector3 _albedo;
    float _fuzz;
};

template<typename Vector3, typename Ray>
MetalT<Vector3, Ray>::MetalT(const Vector3 &albedo, float fuzz) : _albedo(albedo), _fuzz(fuzz)
{}

template<typename Vector3, typename Ray>
bool MetalT<Vector3, Ray>::scatter(const Ray &r_in, const Vector3 &hit_point, const Vector3 &hit_normal, Vector3 &attenuation, Ray &scattered) const
{
    Vector3 reflected = reflect(r_in._dir.normalized(), hit_normal.normalized());
    scattered = Ray(hit_point, reflected + _fuzz * random_in_unit_sphere<Vector3>());
    attenuation = _albedo;
    return scattered._dir.dot(hit_normal) > 0.0f;
}

#endif //AYAKAPATHTRACER_MATERIAL_H
