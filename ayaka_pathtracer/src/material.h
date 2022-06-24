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

template<typename Vector3>
Vector3 refract(const Vector3 &uv, const Vector3 &n, float eta)
{
    auto cos_theta = std::min({-uv.dot(n), 1.0f});
    Vector3 r_out_perp = eta * (uv + cos_theta * n);
    Vector3 r_out_parallel = -std::sqrt(std::abs(1.f - r_out_perp.dot(r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
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

template<typename Vector3, typename Ray>
struct DielectricT : public MaterialT<Vector3, Ray>
{
    explicit DielectricT(float ref_idx);
    bool scatter(const Ray &r_in, const Vector3 &hit_point, const Vector3 &hit_normal, Vector3 &attenuation, Ray &scattered) const override;

    float _ref_idx; // Index of Refraction, known as ir
};

template<typename Vector3, typename Ray>
DielectricT<Vector3, Ray>::DielectricT(float ref_idx) : _ref_idx(ref_idx)
{}

template<typename Vector3, typename Ray>
bool DielectricT<Vector3, Ray>::scatter(const Ray &r_in, const Vector3 &hit_point, const Vector3 &hit_normal, Vector3 &attenuation, Ray &scattered) const
{
    // TODO: To be implemented

    attenuation = Vector3(1.0f, 1.0f, 1.0f);
    double refraction_ratio = _ref_idx; // TODO: enable outward facing ray
    Vector3 reflected = refract(r_in._dir.normalized(), hit_normal.normalized(), refraction_ratio);
    scattered = Ray(hit_point, reflected);
    return true;
}


#endif //AYAKAPATHTRACER_MATERIAL_H
