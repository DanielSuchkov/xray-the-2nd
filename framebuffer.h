#pragma once
#include <cstdint>
#include <cassert>
#include <vector>
#include <SDL2/SDL.h>
#include "utils.h"

class ScreenBufferRGB {
public:
    ScreenBufferRGB(int h, int w)
        : s(get_unique_ptr(createRgbU32Surface(h, w), SDL_FreeSurface))
        , h(h)
        , w(w) {}

    void setPixel(int x, int y, uint32_t color) {
        assert(s.get()->format->BytesPerPixel == 4);
        auto idx = ((s.get()->pitch >> 2) * y) + x;
        static_cast<uint32_t*>(s.get()->pixels)[idx] = color;
    }

    int getHeight() const {
        return h;
    }

    int getWidth() const {
        return w;
    }

    operator bool() const {
        return !!s;
    }

    SDL_Surface* getSdlSurface() {
        return s.get();
    }

private:
    SdlSurfaceUptr s;
    int h;
    int w;

private:
    static SDL_Surface* createRgbU32Surface(int w, int h) {
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

    void setPixel(int x, int y, const C& color) {
        fb[this->idx(x, y)] = color;
    }

    const C& getPixel(int x, int y) const {
        return fb[this->idx(x, y)];
    }

    int getHeight() const {
        return h;
    }

    int getWidth() const {
        return w;
    }

    void fillScreenBuffer(ScreenBufferRGB& sb) {
        assert(sb.getHeight() == getHeight());
        assert(sb.getWidth() == getWidth());
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                sb.setPixel(x, y, colorToU32(this->getPixel(x, y)));
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
