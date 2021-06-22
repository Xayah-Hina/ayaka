#ifndef AYAKA_RASTERIZER_MESH_H
#define AYAKA_RASTERIZER_MESH_H

#include "utils.h"

#include <Eigen/Eigen>
#include <vector>

namespace ayakaras
{

    using namespace Eigen;

    class TriangleFaceMesh
    {
    public:
        typedef std::vector<unsigned int> Faces;
        typedef std::vector<unsigned int> UVIndices;
        typedef std::vector<unsigned int> NormalIndices;

        void load_faces(std::vector<Utils::MeshFaceIndices> &indices)
        {
            size_t num = indices.size();
            faces.reserve(3 * num);
            uvis.reserve(3 * num);
            normalis.reserve(3 * num);
            for (int i = 0; i < num; ++i)
            {
                faces.push_back(indices[i].posIndices.x());
                faces.push_back(indices[i].posIndices.y());
                faces.push_back(indices[i].posIndices.z());
                uvis.push_back(indices[i].texIndices.x());
                uvis.push_back(indices[i].texIndices.y());
                uvis.push_back(indices[i].texIndices.z());
                normalis.push_back(indices[i].normalIndices.x());
                normalis.push_back(indices[i].normalIndices.y());
                normalis.push_back(indices[i].normalIndices.z());
            }
        }

        void clear() { faces.clear(); }

        [[nodiscard]] const Faces &get_faces() const
        {
            return faces;
        }

        [[nodiscard]] const UVIndices &get_uvis() const
        {
            return uvis;
        }

        [[nodiscard]] const NormalIndices &get_normalis() const
        {
            return normalis;
        }

    protected:
        Faces faces;
        UVIndices uvis;
        NormalIndices normalis;
    };
}

#endif //AYAKA_RASTERIZER_MESH_H