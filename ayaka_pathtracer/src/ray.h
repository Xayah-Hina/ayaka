#ifndef AYAKAPATHTRACER_RAY_H
#define AYAKAPATHTRACER_RAY_H

template<typename Vector3>
struct RayT
{
    RayT(Vector3 orig, Vector3 dir);
    Vector3 at(float t) const;

    Vector3 _orig;
    Vector3 _dir;
};

template<typename Vector3>
RayT<Vector3>::RayT(Vector3 orig, Vector3 dir):_orig(orig), _dir(dir)
{}

template<typename Vector3>
Vector3 RayT<Vector3>::at(float t) const
{ return _orig + t * _dir; }

#endif //AYAKAPATHTRACER_RAY_H
