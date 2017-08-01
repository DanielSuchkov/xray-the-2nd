#pragma once
#include "glm/glm.hpp"
#include <cstdint>
#include <cmath>
#include <cassert>
#include <vector>

using SurfaceId = int32_t;

struct Intersection {
    SurfaceId sid; // -1 == no intersection
    glm::vec3 normal;
    float distance;
};

constexpr Intersection no_intersect { -1, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f };

struct Ray {
    glm::vec3 orig;
    glm::vec3 dir;
};

class Sphere {
public:
    Sphere(SurfaceId sid, glm::vec3 pos, float r)
        : sid(sid)
        , pos(pos)
        , r(r) {
        assert(r > 0.0f);
    }

    SurfaceId getSurfaceId() const {
        return sid;
    }

    const glm::vec3 &getPos() const {
        return pos;
    }

    float getRadius() const {
        return r;
    }

    Intersection intersect(const Ray &ray) const {
        auto p = ray.orig - this->pos;
        auto r2 = r * r;
        auto p_d = glm::dot(p, ray.dir);
        if (p_d > 0.0f || glm::dot(p, p) < r2) {
            return no_intersect;
        }
        auto a = p - ray.dir * p_d;
        auto a2 = glm::dot(a, a);
        if (a2 > r2) {
            return no_intersect;
        }

        auto h = std::sqrt(r2 - a2);
        auto i = a - ray.dir * h;
        auto normal = glm::normalize(i);
//        auto intersection = this->pos + i;
//        return { sid, normal, glm::length(intersection - ray.orig) };
        return { sid, normal, glm::length(i - p) };
    }

private:
    SurfaceId sid;
    glm::vec3 pos;
    float r;
};


class GeometryManager {
public:
    Intersection nearestIntersection(const Ray &ray) const {
        Intersection nearest_isect = no_intersect;
        for (auto& g : this->geo) {
            Intersection isect = g.intersect(ray);
            if (nearest_isect.sid == -1 || isect.distance < nearest_isect.distance) {
                nearest_isect = isect;
            }
        }
        return nearest_isect;
    }

    void addGeo(const Sphere &sph) {
        geo.push_back(sph);
    }

private:
    std::vector<Sphere> geo;
};
