#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <geometrymanager.h>

using namespace testing;

TEST(Geometry, IntersectSphere)
{
    Sphere sphere(0, glm::vec3(0.0f, 1.0f, 0.0f), 2.0f);
    Ray ray { glm::vec3(0.0, 1.0, -5.0), glm::vec3(0.0, 0.0, 1.0) };
    auto isect = sphere.intersect(ray);
    EXPECT_EQ(isect.sid, 0);
    EXPECT_FLOAT_EQ(isect.distance, 3.0f);
}

TEST(Geometry, IntersectSphereRev)
{
    Sphere sphere(0, glm::vec3(0.0f, 2.0f, 0.0f), 2.0f);
    Ray ray { glm::vec3(0.0, 2.0, -5.0), glm::vec3(0.0, 0.0, -1.0) };
    auto isect = sphere.intersect(ray);
    EXPECT_EQ(isect.sid, -1);
}

TEST(Geometry, IntersectSphereInside)
{
    Sphere sphere(0, glm::vec3(0.0f, 3.0f, 0.0f), 2.0f);
    Ray ray { glm::vec3(0.0, 3.0, 0.0), glm::vec3(0.0, 0.0, -1.0) };
    auto isect = sphere.intersect(ray);
    EXPECT_EQ(isect.sid, -1);
}
