#include "Eigen/Core"

#include "opencv_viewer/viewer.h"
#include "src/frame_buffer.h"
#include "src/ray.h"
#include "src/shapes.h"
#include "src/world.h"
#include "src/camera.h"
#include "src/random.h"

#include <fstream>
#include <cmath>

std::fstream out("C:/Users/Administrator/Desktop/1.txt");

using Vector3 = Eigen::Vector3f;
using Ray = RayT<Vector3>;
using FrameBuffer = FrameBufferT<Vector3>;
using hit_record = hit_recordT<Vector3>;
using Shape = ShapeT<Vector3>;
using World = WorldT<Shape, Ray, hit_record>;
using Camera = CameraT<Vector3>;

template<typename T>
void clamp(T &src, T min, T max)
{
    if (src < min)
        src = min;
    else if (src > max)
        src = max;
}

//static Vector3 random_vec3(float low_bound, float high_bound)
//{
//    return {Random::random_f(low_bound, high_bound), Random::random_f(low_bound, high_bound), Random::random_f(low_bound, high_bound)};
//};
//
//static Vector3 random_in_unit_sphere()
//{
//    while (true)
//    {
//        auto p = random_vec3(-1, 1);
//        if (p.squaredNorm() >= 1)
//            continue;
//        return p;
//    }
//}

Vector3 random_in_unit_sphere()
{
    auto length = Random::random_f(0.0f, 1.0f);
    auto angle = Random::random_f(0.0f, 2.0f * 3.141592654f);
    auto theta = Random::random_f(0.0f, 2.0f * 3.141592654f);
    return {length * std::cos(theta) * std::cos(angle), length * std::cos(theta) * std::sin(angle), length * std::sin(theta)};
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
    if (depth > 4)
        return {0.0f, 0.0f, 0.0f};

    std::optional<hit_record> opt = world.intersect(ray);
    if (opt.has_value())
    {
        auto hr = opt.value();
        Vector3 p = hr.p;
        Vector3 n = hr.normal;
        auto t = hr.t;
        auto front_face = hr.front_face;

        Vector3 target = p + n + random_in_unit_sphere();

//        return 0.5f * Vector3(n.x() + 1.0f, n.y() + 1.0f, n.z() + 1.0f);
        Ray scattered{p, (target - p).normalized()};
        return 0.5 * ray_color(scattered, world, depth + 1);
    } else
//    {
//        auto d = ray._dir;
//        auto t = 0.5f * (d.y() + 1.0f);
//        return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
//    }
        return {1.0f, 1.0f, 1.0f};
}

static void render_world_to_frame(FrameBuffer &FB, const World &world)
{
    int MSAA = 10;

    for (int row = 0; row < FB._height; ++row)
        for (int col = 0; col < FB._width; ++col)
        {
            Vector3 color = Vector3(0, 0, 0);

            for (int i = 0; i < MSAA; ++i)
                color += ray_color(ray_at_pixel(FB, Vector3(0, 1, 10), row, col), world, 0);
            color /= static_cast<float>(MSAA);
            FB.set_pixel(row, col, color);
        }
}

int main(int argc, char **argv)
{
    World world;
    world.add_shape(std::make_shared<SphereT<Vector3>>(Vector3(0.0f, 0.0f, -1), 0.5f));
    world.add_shape(std::make_shared<SphereT<Vector3>>(Vector3(0, -100.5, -1), 100.0f));

    int width = 800;
    int height = 800;
    FrameBuffer FB(width, height);
    FB.set_clear_color({1.0f, 1.0f, 1.0f});
    FB.clear();
    render_world_to_frame(FB, world);
    Viewer::display_one_frame(FB.data(), FB._width, FB._height);

    out.close();
}
