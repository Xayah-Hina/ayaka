#include "Eigen/Core"

#include "opencv_viewer/viewer.h"
#include "src/frame_buffer.h"
#include "src/ray.h"

using Vector3 = Eigen::Vector3f;
using Ray = RayT<Vector3>;
using FrameBuffer = FrameBufferT<Vector3>;

int main(int argc, char **argv)
{
    FrameBuffer FB(800, 600);
    FB.set_clear_color({1, 1, 1});
    FB.clear();

    for (int i = 0; i < 800; ++i)
        for (int j = 0; j < 600; ++j)
            FB.set_pixel(j, i, {float(i) / 800.f, float(j) / 600.f, 0.25});

    Viewer::display_one_frame(FB.data(), FB.width, FB.height);
}
