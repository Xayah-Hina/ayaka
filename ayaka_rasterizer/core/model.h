#ifndef AYAKA_RASTERIZER_MODEL_H
#define AYAKA_RASTERIZER_MODEL_H

#include "particles.h"
#include "mesh.h"
#include "shader.h"

namespace ayakaras
{
    class TriangleModel
    {
    public:
        explicit TriangleModel(const std::string &filename);
        const Particles &get_particles() const;
        const TriangleFaceMesh &get_mesh() const;
    protected:
        std::unique_ptr<Particles> particles;
        std::unique_ptr<TriangleFaceMesh> mesh;
    private:
        bool setup(const std::string &filename);
    };
}

#endif //AYAKA_RASTERIZER_MODEL_H
