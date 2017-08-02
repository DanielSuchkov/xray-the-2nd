#pragma once
#include <cstdint>
#include <cassert>
#include <vector>
#include <SDL2/SDL.h>
#include "utils.h"

class ScreenBufferRGB {
public:
    ScreenBufferRGB(int h, int w)
        : s(get_unique_ptr(create_rgb_u32_surface(h, w), SDL_FreeSurface))
        , h(h)
        , w(w) {}

    void set_pixel(int x, int y, uint32_t color) {
        assert(s.get()->format->BytesPerPixel == 4);
        auto idx = ((s.get()->pitch >> 2) * y) + x;
        static_cast<uint32_t*>(s.get()->pixels)[idx] = color;
    }

    int get_height() const {
        return h;
    }

    int get_width() const {
        return w;
    }

    operator bool() const {
        return !!s;
    }

    SDL_Surface* get_SDL_surface() {
        return s.get();
    }

private:
    SdlSurfaceUptr s;
    int h;
    int w;

private:
    static SDL_Surface* create_rgb_u32_surface(int w, int h) {
        //The final optimized image
        SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, uint32_t(0xFF) << 16, 0xFF << 8, 0xFF << 0, 0x00);
        return surface;
        //    return get_unique_ptr(surface, SDL_FreeSurface);
    }
};

template <typename C>
class Framebuffer {
public:
    Framebuffer(int h, int w)
        : fb(h * w)
        , h(h)
        , w(w) {}

    void set_pixel(int x, int y, const C& color) {
        fb[this->idx(x, y)] = color;
    }

    const C& get_pixel(int x, int y) const {
        return fb[this->idx(x, y)];
    }

    void add_to_pixel(int x, int y, const C& color) {
        fb[this->idx(x, y)] += color;
    }

    int get_height() const {
        return h;
    }

    int get_width() const {
        return w;
    }

    void fill_screen_buffer(ScreenBufferRGB& sb) {
        assert(sb.get_height() == get_height());
        assert(sb.get_width() == get_width());
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                sb.set_pixel(x, y, color_to_u32(this->get_pixel(x, y)));
            }
        }
    }

private:
    std::vector<C> fb;
    int h;
    int w;

private:
    inline int idx(int x, int y) const {
        return y * w + x;
    }
};

using FramebufferRGB = Framebuffer<vec3>;
