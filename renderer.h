#pragma once
#include "framebuffer.h"

class Renderer {
public:
    Renderer() {

    }

    void draw(FramebufferRGB& fb) {
        int cnt = 0;
        for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
            for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
                fb.set_pixel(j, i, vec3(1.0, 0.2, 0.2));
            }
        }
        cnt++;
        for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
            for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
                fb.set_pixel(j, i, vec3(0.2, 0.8, 0.2));
            }
        }
        cnt++;
        for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
            for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
                fb.set_pixel(j, i, vec3(0.2, 0.2, 0.8));
            }
        }
    }
};
