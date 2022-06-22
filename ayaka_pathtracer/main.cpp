#include "Eigen/Core"

#include "opencv_viewer/viewer.h"
#include "src/frame_buffer.h"
#include "src/ray.h"
#include "src/shapes.h"
#include "src/world.h"

using Vector3 = Eigen::Vector3f;
using Ray = RayT<Vector3>;
using FrameBuffer = FrameBufferT<Vector3>;
using hit_record = hit_recordT<Vector3>;
using Shape = ShapeT<Vector3>;
using World = WorldT<Shape>;

static Ray ray_at_pixel(const FrameBuffer &frame, const Vector3 &orig, int row, int col)
{
    float x_bios = static_cast<float>(frame._width) / 2.0f;
    float y_bios = static_cast<float>(frame._height) / 2.0f;

    float x_target = (static_cast<float>(col) - x_bios) / x_bios;
    float y_target = (y_bios - static_cast<float>(row)) / y_bios;

    Vector3 dir = (Vector3(x_target, y_target, 0) - orig).normalized();
    return {orig, dir};
}

static Vector3 get_color(const Ray &ray)
{
    Vector3 dir = ray._dir.normalized();
    auto t = 0.5f * dir.y() + 1.0f;
    return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
}

int main(int argc, char **argv)
{
    int width = 800;
    int height = 800;
    FrameBuffer FB(width, height);
    FB.set_clear_color({1.0f, 1.0f, 1.0f});
    FB.clear();

    World world;
    world.add_shape(std::make_shared<SphereT<Vector3>>(Vector3(0, 0, -5), 0.5f));
    world.add_shape(std::make_shared<SphereT<Vector3>>(Vector3(0, 0.4, -5), 0.3f));

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
        {
            std::optional<hit_record> opt = std::nullopt;
            auto closest_so_far = std::numeric_limits<float>::max();
            for (const auto &pair: world._shapes)
            {
                auto s = pair.second;
                auto r = ray_at_pixel(FB, Vector3(0, 0, 10), j, i);
                auto res = s->intersect(r._orig, r._dir, 0.1f, closest_so_far);
                if (res.has_value())
                {
                    closest_so_far = res.value().t;
                    opt = res;
                }
            }

            if (opt.has_value())
            {
                auto hr = opt.value();
                auto n = hr.normal;
                auto c = 0.5f * Vector3(n.x() + 1.0f, n.y() + 1.0f, n.z() + 1.0f);
                FB.set_pixel(j, i, c);
            } else
                FB.set_pixel(j, i, {1.0f, 1.0f, 1.0f});
        }

    Viewer::display_one_frame(FB.data(), FB._width, FB._height);
}
