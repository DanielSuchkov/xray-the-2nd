#pragma once
#include "utils.h"
#include <cstdint>
#include <cmath>
#include <cassert>
#include <vector>

using SurfaceId = int32_t;

struct Intersection {
    SurfaceId sid; // -1 == no intersection
    vec3 normal;
    float distance;

    static constexpr Intersection zero() {
        return { -1, vec3(0.0f, 0.0f, 0.0f), 0.0f };
    }
};

struct Ray {
    vec3 orig;
    vec3 dir;
};

class Sphere {
public:
    Sphere(SurfaceId sid, vec3 pos, float r)
        : sid(sid)
        , pos(pos)
        , r(r) {
        assert(this->r > 0.0f);
    }

    SurfaceId get_surface_id() const {
        return this->sid;
    }

    const vec3& get_pos() const {
        return this->pos;
    }

    float get_radius() const {
        return this->r;
    }

    Intersection intersect(const Ray& ray) const {
        auto p = ray.orig - this->pos;
        auto r2 = this->r * this->r;
        auto p_d = glm::dot(p, ray.dir);
        if (p_d > 0.0f || glm::dot(p, p) < r2) {
            return Intersection::zero();
        }
        auto a = p - ray.dir * p_d;
        auto a2 = glm::dot(a, a);
        if (a2 > r2) {
            return Intersection::zero();
        }

        auto h = std::sqrt(r2 - a2);
        auto i = a - ray.dir * h;
        auto normal = glm::normalize(i);
//        auto intersection = this->pos + i;
//        return { sid, normal, glm::length(intersection - ray.orig) };
        return { this->sid, normal, glm::length(i - p) };
    }

private:
    SurfaceId sid;
    vec3 pos;
    float r;
};

class GeometryManager {
public:
    Intersection nearest_intersection(const Ray& ray) const {
        Intersection nearest_isect = Intersection::zero();
        for (auto& g : this->geo) {
            Intersection isect = g.intersect(ray);
            if (nearest_isect.sid == -1 || isect.distance < nearest_isect.distance) {
                nearest_isect = isect;
            }
        }
        return nearest_isect;
    }

    void add_geo(const Sphere& sph) {
        this->geo.push_back(sph);
    }

private:
    std::vector<Sphere> geo;
};
