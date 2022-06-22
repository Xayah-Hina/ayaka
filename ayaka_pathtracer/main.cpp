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
using World = WorldT<Shape, Ray, hit_record>;

static Ray ray_at_pixel(const FrameBuffer &frame, const Vector3 &orig, int row, int col)
{
    float x_bios = static_cast<float>(frame._width) / 2.0f;
    float y_bios = static_cast<float>(frame._height) / 2.0f;

    float x_target = (static_cast<float>(col) - x_bios) / x_bios;
    float y_target = (y_bios - static_cast<float>(row)) / y_bios;

    Vector3 dir = (Vector3(x_target, y_target, 0) - orig).normalized();
    return {orig, dir};
}

static void render_world_to_frame(FrameBuffer &FB, const World &world)
{
    for (int row = 0; row < FB._height; ++row)
        for (int col = 0; col < FB._width; ++col)
        {
            auto r = ray_at_pixel(FB, Vector3(0, 0, 10), row, col);
            std::optional<hit_record> opt = world.intersect(r);

            if (opt.has_value())
            {
                auto hr = opt.value();
                auto n = hr.normal;
                Vector3 c = 0.5f * Vector3(n.x() + 1.0f, n.y() + 1.0f, n.z() + 1.0f);
                FB.set_pixel(row, col, c);
            } else
                FB.set_pixel(row, col, {1.0f, 1.0f, 1.0f});
        }
}

int main(int argc, char **argv)
{
    World world;
    world.add_shape(std::make_shared<SphereT<Vector3>>(Vector3(0.0f, 0.0f, -5), 0.5f));
    world.add_shape(std::make_shared<SphereT<Vector3>>(Vector3(0.0f, 0.4f, -5), 0.3f));

    int width = 800;
    int height = 800;
    FrameBuffer FB(width, height);
    FB.set_clear_color({1.0f, 1.0f, 1.0f});
    FB.clear();
    render_world_to_frame(FB, world);
    Viewer::display_one_frame(FB.data(), FB._width, FB._height);
}
