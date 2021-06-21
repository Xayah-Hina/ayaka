#ifndef AYAKA_RASTERIZER_MODEL_H
#define AYAKA_RASTERIZER_MODEL_H

#include "particles.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

#include <vector>

namespace ayakaras
{
    struct Material
    {
        Texture diffuse;
        Texture specular;
        float shininess{};
    };

    class TriangleModel
    {
    public:
        explicit TriangleModel(const std::string &filename);
        [[nodiscard]] const std::vector<Particles> &get_particles() const;
        [[nodiscard]] const std::vector<TriangleFaceMesh> &get_meshes() const;
        [[nodiscard]] const std::vector<Material> &get_materials() const;
        [[nodiscard]] const unsigned int get_meshsize() const;
    protected:
        std::vector<Particles> particles;
        std::vector<TriangleFaceMesh> meshes;
        std::vector<Material> materials;
    private:
        bool setup(const std::string &filename);
    };
}

#endif //AYAKA_RASTERIZER_MODEL_H
