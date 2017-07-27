#pragma once
#include <cstdint>
#include <cassert>
#include <SDL2/SDL.h>
#include "utils.h"

class FramebufferRGB
{
public:
    FramebufferRGB(int h, int w)
        : s(get_unique_ptr(createRgbU32Surface(h, w), SDL_FreeSurface))
        , h(h)
        , w(w) {}

    void setPixel(int x, int y, uint32_t color) {
        assert(s.get()->format->BytesPerPixel == 4);
        *(static_cast<uint32_t *>(s.get()->pixels) + ((s.get()->pitch >> 2) * y) + x) = color;
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
