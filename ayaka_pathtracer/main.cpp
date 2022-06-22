#include "Eigen/Core"

#include "opencv_viewer/viewer.h"
#include "src/frame_buffer.h"
#include "src/ray.h"
#include "src/shapes.h"
#include "src/world.h"

using Vector3 = Eigen::Vector3f;
using Ray = RayT<Vector3>;
using FrameBuffer = FrameBufferT<Vector3>;
using Shape = ShapeT<Vector3>;
using World = WorldT<Shape>;

static Ray ray_at_pixel(const FrameBuffer &frame, const Vector3 &orig, int row, int col)
{
    float x_bios = static_cast<float>(frame.width) / 2.0f;
    float y_bios = static_cast<float>(frame.height) / 2.0f;

    float x_target = (static_cast<float>(col) - x_bios) / x_bios;
    float y_target = (y_bios - static_cast<float>(row)) / y_bios;

    Vector3 dir = (Vector3(x_target, y_target, 0) - orig).normalized();
    return {orig, dir};
}

static Vector3 get_color(const Ray &ray)
{
    Vector3 dir = ray.dir.normalized();
    auto t = 0.5f * dir.y() + 1.0f;
    return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
}

int main(int argc, char **argv)
{
    int width = 800;
    int height = 800;
    FrameBuffer FB(width, height);
    FB.set_clear_color({1, 1, 1});
    FB.clear();

    World world;
    world.add_shape(std::make_shared<SphereT<Vector3>>(Vector3(0, 0, -1), 0.5f));

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            for (auto &pair: world.shapes)
            {
                auto _s = pair.second;
                auto _r = ray_at_pixel(FB, Vector3(0, 0, 1), j,i);
                auto res = _s->intersect(_r.orig, _r.dir, 0.1f, 100.0f);
                if (res.has_value())
                {
                    FB.set_pixel(j, i, {1.0f, 1.0f, 1.0f});
                } else
                {
                    FB.set_pixel(j, i, {0.0f, 0.0f, 0.0f});
                }
            }

    Viewer::display_one_frame(FB.data(), FB.width, FB.height);
}
