#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "geometrymanager.h"
#include "utils.h"

using namespace testing;

TEST(Geometry, IntersectSphere) {
    Sphere sphere(0, vec3(0.0f, 1.0f, 0.0f), 2.0f);
    Ray ray { vec3(0.0, 1.0, -5.0), vec3(0.0, 0.0, 1.0) };
    auto isect = sphere.intersect(ray);
    EXPECT_EQ(isect.sid, 0);
    EXPECT_FLOAT_EQ(isect.distance, 3.0f);
    EXPECT_EQ(isect.normal, vec3(0.0, 0.0, -1.0));
}

TEST(Geometry, IntersectSphereRev) {
    Sphere sphere(0, vec3(0.0f, 2.0f, 0.0f), 2.0f);
    Ray ray { vec3(0.0, 2.0, -5.0), vec3(0.0, 0.0, -1.0) };
    auto isect = sphere.intersect(ray);
    EXPECT_EQ(isect.sid, -1);
}

TEST(Geometry, IntersectSphereInside) {
    Sphere sphere(0, vec3(0.0f, 3.0f, 0.0f), 2.0f);
    Ray ray { vec3(0.0, 3.0, 0.0), vec3(0.0, 0.0, -1.0) };
    auto isect = sphere.intersect(ray);
    EXPECT_EQ(isect.sid, -1);
}

TEST(Geometry, GeometryManager1SphCollision) {
    Sphere sphere(0, vec3(0.0f, 1.0f, 0.0f), 2.0f);
    Ray ray { vec3(0.0, 1.0, -5.0), vec3(0.0, 0.0, 1.0) };
    GeometryManager gm;
    gm.add_geo(sphere);
    auto isect = gm.nearest_intersection(ray);
    EXPECT_EQ(isect.sid, 0);
    EXPECT_FLOAT_EQ(isect.distance, 3.0f);
    EXPECT_EQ(isect.normal, vec3(0.0, 0.0, -1.0));
}

TEST(Geometry, GeometryManager2SphCollision) {
    Sphere sphere(0, vec3(0.0f, 1.0f, 0.0f), 2.0f);
    Sphere sphere2(0, vec3(0.0f, 1.0f, 1.0f), 2.0f);
    Ray ray { vec3(0.0, 1.0, -5.0), vec3(0.0, 0.0, 1.0) };
    GeometryManager gm;
    gm.add_geo(sphere);
    gm.add_geo(sphere2);
    auto isect = gm.nearest_intersection(ray);
    EXPECT_EQ(isect.sid, 0);
    EXPECT_FLOAT_EQ(isect.distance, 3.0f);
    EXPECT_EQ(isect.normal, vec3(0.0, 0.0, -1.0));
}
