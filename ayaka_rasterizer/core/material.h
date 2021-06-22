#ifndef AYAKA_RASTERIZER_MATERIAL_H
#define AYAKA_RASTERIZER_MATERIAL_H

#include "texture.h"

namespace ayakaras
{
    struct Material
    {
        Texture diffuse;
        Texture specular;
        float shininess{};
    };
}

#endif //AYAKA_RASTERIZER_MATERIAL_H
