#pragma once
#include "framebuffer.h"

class Renderer {
public:
    Renderer() {

    }

    void draw(FramebufferRGB &fb) {
        int cnt = 0;
        for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
            for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
                fb.setPixel(j, i, colorU32(0xBB, 0x10, 0x10));
            }
        }
        cnt++;
        for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
            for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
                fb.setPixel(j, i, colorU32(0x10, 0xBB, 0x10));
            }
        }
        cnt++;
        for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
            for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
                fb.setPixel(j, i, colorU32(0x10, 0x10, 0xBB));
            }
        }
    }
};
