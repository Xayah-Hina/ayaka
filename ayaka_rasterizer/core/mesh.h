#ifndef AYAKA_RASTERIZER_MESH_H
#define AYAKA_RASTERIZER_MESH_H

#include <Eigen/Eigen>
#include <vector>

namespace ayakaras
{

    using namespace Eigen;

    class TriangleFaceMesh
    {
    public:
        typedef std::vector<unsigned int> Faces;

        void load_faces(std::vector<Vector3i> &indices)
        {
            size_t num = indices.size();
            faces.reserve(3 * num);
            for (int i = 0; i < num; ++i)
            {
                faces.push_back(indices[i].x());
                faces.push_back(indices[i].y());
                faces.push_back(indices[i].z());
            }
        }

        void clear() { faces.clear(); }

        const Faces &get_faces() const
        {
            return faces;
        }

    protected:
        Faces faces;
    };
}

#endif //AYAKA_RASTERIZER_MESH_H