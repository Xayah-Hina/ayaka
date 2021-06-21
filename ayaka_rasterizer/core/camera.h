#ifndef AYAKA_RASTERIZER_CAMERA_H
#define AYAKA_RASTERIZER_CAMERA_H

#include "Eigen/Eigen"

namespace ayakaras
{
    using namespace Eigen;

    class Camera
    {
    public:
        Matrix4f get_model_matrix(float rotation_x_angle, float rotation_y_angle, float rotation_z_angle) const;

        Matrix4f get_view_matrix() const;

        Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar) const;

    protected:
        float zoom = 1.f;
        const float PI = 3.1415926f;
    };
}

#endif //AYAKA_RASTERIZER_CAMERA_H
