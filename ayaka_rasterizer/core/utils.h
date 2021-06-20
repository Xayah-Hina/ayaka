#ifndef AYAKA_RASTERIZER_UTILS_H
#define AYAKA_RASTERIZER_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Eigen>

using namespace Eigen;

class Utils
{
public:
    struct MeshFaceIndices
    {
        Vector3i posIndices;
        Vector3i texIndices;
        Vector3i normalIndices;
    };
public:
    static void tokenize(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters = " ")
    {
        std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        std::string::size_type pos = str.find_first_of(delimiters, lastPos);

        while (std::string::npos != pos || std::string::npos != lastPos)
        {
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            lastPos = str.find_first_not_of(delimiters, pos);
            pos = str.find_first_of(delimiters, lastPos);
        }
    }

    static bool loadObj(const std::string &filename, std::vector<Vector3f> *positions, std::vector<Vector3i> *indices, std::vector<Vector2f> *uv = nullptr,
                        std::vector<Vector3f> *normals = nullptr)
    {
        std::clog << "LOADING: " << filename << std::endl;

        std::string path = PROJECT_SOURCE_DIR + std::string("/../models/") + filename;

        std::ifstream filestream;
        filestream.open(path.c_str());

        if (filestream.fail())
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return false;
        }

        std::string line_stream;
        bool vt = false;
        bool vn = false;

        std::vector<std::string> pos_buffer;
        std::vector<std::string> f_buffer;

        while (getline(filestream, line_stream))
        {
            std::stringstream str_stream(line_stream);
            std::string type_str;
            str_stream >> type_str;

            if (type_str == "v")
            {
                Vector3f pos;
                pos_buffer.clear();
                std::string parse_str = line_stream.substr(line_stream.find("v") + 1);
                tokenize(parse_str, pos_buffer);
                for (unsigned int i = 0; i < 3; i++)
                    pos[i] = stof(pos_buffer[i]);

                positions->push_back(pos);
            } else if (type_str == "vt")
            {
                if (uv != nullptr)
                {
                    Vector2f tex;
                    pos_buffer.clear();
                    std::string parse_str = line_stream.substr(line_stream.find("vt") + 2);
                    tokenize(parse_str, pos_buffer);
                    for (unsigned int i = 0; i < 2; i++)
                        tex[i] = stof(pos_buffer[i]);

                    uv->push_back(tex);
                    vt = true;
                }
            } else if (type_str == "vn")
            {
                if (normals != nullptr)
                {
                    Vector3f nor;
                    pos_buffer.clear();
                    std::string parse_str = line_stream.substr(line_stream.find("vn") + 2);
                    tokenize(parse_str, pos_buffer);
                    for (unsigned int i = 0; i < 3; i++)
                        nor[i] = stof(pos_buffer[i]);

                    normals->push_back(nor);
                    vn = true;
                }
            } else if (type_str == "f")
            {
                MeshFaceIndices faceIndex;
                if (vn && vt)
                {
                    f_buffer.clear();
                    std::string parse_str = line_stream.substr(line_stream.find("f") + 1);
                    tokenize(parse_str, f_buffer);
                    for (int i = 0; i < 3; ++i)
                    {
                        pos_buffer.clear();
                        tokenize(f_buffer[i], pos_buffer, "/");
                        faceIndex.posIndices[i] = stoi(pos_buffer[0]);
                        faceIndex.texIndices[i] = stoi(pos_buffer[1]);
                        faceIndex.normalIndices[i] = stoi(pos_buffer[2]);
                    }
                } else if (vn)
                {
                    f_buffer.clear();
                    std::string parse_str = line_stream.substr(line_stream.find("f") + 1);
                    tokenize(parse_str, f_buffer);
                    for (int i = 0; i < 3; ++i)
                    {
                        pos_buffer.clear();
                        tokenize(f_buffer[i], pos_buffer, "/");
                        faceIndex.posIndices[i] = stoi(pos_buffer[0]);
                        faceIndex.normalIndices[i] = stoi(pos_buffer[1]);
                    }
                } else if (vt)
                {
                    f_buffer.clear();
                    std::string parse_str = line_stream.substr(line_stream.find("f") + 1);
                    tokenize(parse_str, f_buffer);
                    for (int i = 0; i < 3; ++i)
                    {
                        pos_buffer.clear();
                        tokenize(f_buffer[i], pos_buffer, "/");
                        faceIndex.posIndices[i] = stoi(pos_buffer[0]);
                        faceIndex.texIndices[i] = stoi(pos_buffer[1]);
                    }
                } else
                {
                    f_buffer.clear();
                    std::string parse_str = line_stream.substr(line_stream.find("f") + 1);
                    tokenize(parse_str, f_buffer);
                    for (int i = 0; i < 3; ++i)
                    {
                        faceIndex.posIndices[i] = stoi(f_buffer[i]);
                    }
                }
                indices->push_back(faceIndex.posIndices);
            } else if (type_str == "mtllib")
            {

            } else if (type_str == "usemtl")
            {

            } else
            {
                std::clog << "ignore line: " << line_stream << std::endl;
            }
        }
        filestream.close();
        return true;
    }
};

#endif //AYAKA_RASTERIZER_UTILS_H
