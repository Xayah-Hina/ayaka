#include "camera.h"

using namespace ayakaras;

Matrix4f Camera::get_model_matrix(float rotation_x_angle, float rotation_y_angle, float rotation_z_angle) const
{
    Matrix4f model = Matrix4f::Identity();

    Matrix4f scale;
    scale << zoom, 0, 0, 0, 0, zoom, 0, 0, 0, 0, zoom, 0, 0, 0, 0, 1;

    Matrix4f rotation_x, rotation_y, rotation_z;
    rotation_x << 1, 0, 0, 0, 0, cos(rotation_x_angle / 180.f * PI), -sin(rotation_x_angle / 180.f * PI), 0, 0, sin(rotation_x_angle / 180.f * PI), cos(
            rotation_x_angle / 180.f * PI), 0, 0, 0, 0, 1;
    rotation_y << cos(rotation_y_angle / 180.f * PI), 0, sin(rotation_y_angle / 180.f * PI), 0, 0, 1, 0, 0, -sin(rotation_y_angle / 180.f * PI), 0, cos(
            rotation_y_angle / 180.f * PI), 0, 0, 0, 0, 1;
    rotation_z << cos(rotation_z_angle / 180.f * PI), -sin(rotation_z_angle / 180.f * PI), 0, 0, sin(rotation_z_angle / 180.f * PI), cos(
            rotation_z_angle / 180.f * PI), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
    model = rotation_x * rotation_y * rotation_z * scale * model;
    return model;
}

Matrix4f Camera::get_view_matrix() const
{
    Matrix4f view;
    view << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, -5, 0, 0, 0, 1;
    return view;
}

Matrix4f Camera::get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar) const
{
    Matrix4f projection = Matrix4f::Identity();

    float harf_height_near = -zNear * tan(eye_fov / 360.f * PI);
    float harf_width_near = harf_height_near * aspect_ratio;
    float harf_depth_near = 0.5f * (zNear - zFar);

    Matrix4f perspective;
    perspective << zNear, 0, 0, 0, 0, zNear, 0, 0, 0, 0, zNear + zFar, -zNear * zFar, 0, 0, 1, 0;

    Matrix4f shift;
    shift << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, -(zNear + zFar) / 2.f, 0, 0, 0, 1;

    Matrix4f canonize;
    canonize << 1.f / harf_width_near, 0, 0, 0, 0, 1.f / harf_height_near, 0, 0, 0, 0, 1.f / harf_depth_near, 0, 0, 0, 0, 1.f;

    projection = canonize * shift * perspective * projection;

    return projection;
}