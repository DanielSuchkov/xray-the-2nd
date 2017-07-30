#pragma once
#include "glm/glm.hpp"
#include <cstdint>
#include <vector>

using SurfaceId = int32_t;

struct Intersection {
    glm::vec3 normal;
    float distance;
    SurfaceId sid; // -1 == no intersection
};

class Sphere {

};


class GeometryManager {
public:

    Intersection nearestIntersection(const glm::vec3 &orig, const glm::vec3 &dir) const ;

private:
    std::vector<Sphere> geo_;
};
