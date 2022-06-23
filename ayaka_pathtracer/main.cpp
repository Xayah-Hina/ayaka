#include "Eigen/Core"

#include "opencv_viewer/viewer.h"
#include "src/frame_buffer.h"
#include "src/ray.h"
#include "src/shapes.h"
#include "src/world.h"
#include "src/camera.h"
#include "src/random.h"
#include "src/material.h"

#include <fstream>

using Vector3 = Eigen::Vector3f;
using Camera = CameraT<Vector3>;
using Ray = RayT<Vector3>;
using FrameBuffer = FrameBufferT<Vector3>;
using Material = MaterialT<Vector3, Ray>;
using hit_record = hit_recordT<Vector3, Material>;
using Shape = ShapeT<Vector3, Material>;
using World = WorldT<Shape, Ray, hit_record>;

template<typename T>
void clamp(T &src, T min, T max)
{
    if (src < min)
        src = min;
    else if (src > max)
        src = max;
}

static Ray ray_at_pixel(const FrameBuffer &frame, const Vector3 &orig, int row, int col)
{
    float x_bios = static_cast<float>(frame._width) / 2.0f;
    float y_bios = static_cast<float>(frame._height) / 2.0f;

    float x_target = (static_cast<float>(col) - x_bios + Random::random_f(0.f, 1.f)) / x_bios;
    float y_target = (y_bios - static_cast<float>(row) + Random::random_f(0.f, 1.f)) / y_bios;

    Vector3 dir = (Vector3(x_target, y_target, 0) - orig).normalized();
    return {orig, dir};
}

static Vector3 ray_color(const Ray &ray, const World &world, int depth)
{
    if (depth < 0)
        return {0.0f, 0.0f, 0.0f};

    std::optional<hit_record> opt = world.intersect(ray);
    if (opt.has_value())
    {
        auto hr = opt.value();
        Vector3 p = hr.p;
        Vector3 n = hr.normal;
        auto t = hr.t;
        auto front_face = hr.front_face;
        auto mat_ptr = hr.mat_ptr;


//        return 0.5f * Vector3(n.x() + 1.0f, n.y() + 1.0f, n.z() + 1.0f);

//        Vector3 target = p + n + random_in_unit_sphere().normalized(); // use true Lambertian Reflection
//        Ray scattered{p, (target - p).normalized()};
//        return 0.5 * ray_color(scattered, world, depth - 1);

        Ray scattered{Vector3::Zero(), Vector3::Zero()};
        Vector3 attenuation{1.0f, 1.0f, 1.0f};
        if (mat_ptr->scatter(ray, p, n, attenuation, scattered))
            return attenuation.cwiseProduct(ray_color(scattered, world, depth - 1));
        return {0.0f, 0.0f, 0.0f};
    } else
    {
        auto d = ray._dir;
        auto t = 0.5f * (d.y() + 1.0f);
        return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
    }
}

static void render_world_to_frame(FrameBuffer &FB, const World &world)
{
    int MSAA = 30;

    for (int row = 0; row < FB._height; ++row)
        for (int col = 0; col < FB._width; ++col)
        {
            Vector3 color{0, 0, 0};
            for (int i = 0; i < MSAA; ++i)
                color += ray_color(ray_at_pixel(FB, Vector3(0, 1, 10), row, col), world, 5);
            color /= static_cast<float>(MSAA);
            FB.set_pixel(row, col, color);
        }
}

int main(int argc, char **argv)
{
    World world;

    {
        auto lambertian = std::make_shared<LambertianT<Vector3, Ray>>(Vector3(0.9f, 0.6f, 0.7f));
        auto metal = std::make_shared<MetalT<Vector3, Ray>>(Vector3(0.8f, 0.8f, 0.8f), 0.3f);
        auto sphere1 = std::make_shared<SphereT<Vector3, Material>>(Vector3(0.0f, 0.0f, -1), 0.5f);
        auto sphere2 = std::make_shared<SphereT<Vector3, Material>>(Vector3(0, -100.5, -1), 100.0f);
        sphere1->_mat_ptr = lambertian;
        sphere2->_mat_ptr = metal;
        world.add_shape(sphere1);
        world.add_shape(sphere2);
    }

    int width = 800;
    int height = 800;
    FrameBuffer FB(width, height);
    FB.set_clear_color({1.0f, 1.0f, 1.0f});
    FB.clear();
    render_world_to_frame(FB, world);
    FB.gamma_correct(1.5f);
    Viewer::display_one_frame(FB.data(), FB._width, FB._height);
}
