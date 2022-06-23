#ifndef AYAKAPATHTRACER_CAMERA_H
#define AYAKAPATHTRACER_CAMERA_H

template <typename Vector3>
struct CameraT
{
    Vector3 origin;
    Vector3 lower_left_corner;
    Vector3 horizontal;
    Vector3 vertical;
};

#endif //AYAKAPATHTRACER_CAMERA_H
