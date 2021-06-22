#include "raytracer.h"

#include <iostream>
#include <string>
#include <fstream>

#include "opencv2/opencv.hpp"

const unsigned int width = 2000u;
const unsigned int height = 1500u;

void exportppm(const unsigned int w, const unsigned int h)
{
    std::ofstream os(std::string(OUTPUT_DIR) + "/test.ppm", std::ios_base::trunc | std::ios_base::out);

    os << "P3\n" << w << " " << h << "\n255\n";

    for (int j = h - 1; j >= 0; --j)
    {
        for (int i = 0; i < w; ++i)
        {
            float r = float(i) / float(w);
            float g = float(j) / float(h);
            float b = 0.2;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);
            os << ir << " " << ig << " " << ib << "\n";
        }
    }
}

int main(int argc, char **argv)
{
    ayakaray::Raytracer rtr(width, height);
    exportppm(rtr.get_width(), rtr.get_height());
}
