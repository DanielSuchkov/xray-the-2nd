#pragma once
#include "framebuffer.h"
#include <random>

class Renderer {
public:
    Renderer() {
    }

    void draw(FramebufferRGB& fb) {
        this->iterate_over_screen(fb);
    }

private:
    void iterate_over_screen(FramebufferRGB& fb) const {
        const auto x_res = fb.get_width();
        const auto y_res = fb.get_height();
        for (int y = 0; y < y_res; ++y) {
            for (int x = 0; x < x_res; ++x) {
                vec2 jitter(thread_rng_f32() / 2.0f, thread_rng_f32() / 2.0f);
                auto sample = vec2(x, y) + jitter;
                auto color = this->trace_from_screen(sample);
                fb.set_pixel(x, y, color);
            }
        }
    }

    vec3 trace_from_screen(const vec2& sample) const {
        return vec3(1.0f * ((int(sample.x) / 20 % 2 + int(sample.y) / 20 % 2) % 2));
    }
};
