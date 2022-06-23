#ifndef AYAKAPATHTRACER_WORLD_H
#define AYAKAPATHTRACER_WORLD_H

#include <map>
#include <memory>

template<typename Shape, typename Ray, typename hit_record>
struct WorldT
{
    int add_shape(std::shared_ptr<Shape> ptr);
    void delete_shape(int id);
    std::optional<hit_record> intersect(const Ray &r) const;

    std::map<int, std::shared_ptr<Shape>> _shapes;
    static int GLOBAL_ID;
};

template<typename Shape, typename Ray, typename hit_record>
int WorldT<Shape, Ray, hit_record>::GLOBAL_ID = 0;

template<typename Shape, typename Ray, typename hit_record>
int WorldT<Shape, Ray, hit_record>::add_shape(std::shared_ptr<Shape> ptr)
{
    _shapes[GLOBAL_ID] = ptr;
    return GLOBAL_ID++;
}

template<typename Shape, typename Ray, typename hit_record>
void WorldT<Shape, Ray, hit_record>::delete_shape(int id)
{
    _shapes.erase(id);
}

template<typename Shape, typename Ray, typename hit_record>
std::optional<hit_record> WorldT<Shape, Ray, hit_record>::intersect(const Ray &r) const
{
    std::optional<hit_record> opt = std::nullopt;
    auto closest_so_far = std::numeric_limits<float>::max();
    for (const auto &pair: _shapes)
    {
        std::shared_ptr<Shape> s = pair.second;
        std::optional<hit_record> res = s->intersect(r._orig, r._dir, 0.0f, closest_so_far);
        if (res.has_value())
        {
            closest_so_far = res.value().t;
            opt = res;
        }
    }
    return opt;
}

#endif //AYAKAPATHTRACER_WORLD_H
