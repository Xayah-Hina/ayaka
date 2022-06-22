#ifndef AYAKAPATHTRACER_WORLD_H
#define AYAKAPATHTRACER_WORLD_H

#include <map>
#include <memory>

template<typename Shape>
struct WorldT
{
    int add_shape(std::shared_ptr<Shape> ptr);
    void delete_shape(int id);

    std::map<int, std::shared_ptr<Shape>> _shapes;
    static int GLOBAL_ID;
};

template<typename Shape>
int WorldT<Shape>::GLOBAL_ID = 0;

template<typename Shape>
int WorldT<Shape>::add_shape(std::shared_ptr<Shape> ptr)
{
    _shapes[GLOBAL_ID] = ptr;
    return GLOBAL_ID++;
}

template<typename Shape>
void WorldT<Shape>::delete_shape(int id)
{
    _shapes.erase(id);
}

#endif //AYAKAPATHTRACER_WORLD_H
