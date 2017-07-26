#include <string>
#include <iostream>
#include <memory>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <SDL2/SDL.h>

template <typename T>
using deleter_t = void (*)(T*);

template <typename T>
using unique_ptr_with_deleter_t = std::unique_ptr<T, deleter_t<T>>;

template <typename T>
std::unique_ptr<T> get_unique_ptr(T* t) {
    return std::unique_ptr<T>(t);
}

template <typename T>
unique_ptr_with_deleter_t<T> get_unique_ptr(T* t, deleter_t<T> del) {
    return std::unique_ptr<T, deleter_t<T>>(t, del);
}

using SdlSurfaceUptr = unique_ptr_with_deleter_t<SDL_Surface>;
using SdlWindowUptr = unique_ptr_with_deleter_t<SDL_Window>;

SdlSurfaceUptr createRgbU32Surface(int w, int h) {
    //The final optimized image
    SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, uint32_t(0xFF) << 16, 0xFF << 8, 0xFF << 0, 0x00);
    return get_unique_ptr(surface, SDL_FreeSurface);
}

void setPixel(SDL_Surface *s, int x, int y, uint32_t color) {
    assert(s->format->BytesPerPixel == 4);
    *(static_cast<uint32_t *>(s->pixels) + ((s->pitch >> 2) * y) + x) = color;
}

uint32_t colorU32(uint32_t r, uint32_t g, uint32_t b) {
    return (r << 16) | (g << 8) | b;
}

int main(int, char*[]) {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    const int SCREEN_WIDTH = 300;
    const int SCREEN_HEIGHT = 300;

    //Create window
    SDL_Window* wptr = SDL_CreateWindow("xRay The 2nd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SdlWindowUptr window = get_unique_ptr(wptr, SDL_DestroyWindow);
    if (window == nullptr) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window.get());

    auto stretchedSurface = createRgbU32Surface(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (stretchedSurface == nullptr) {
        printf("Failed to load media!\n");
        return 1;
    }
    bool quit = false;

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    int cnt = 0;
    for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
        for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
            setPixel(stretchedSurface.get(), j, i, colorU32(0xBB, 0x10, 0x10));
        }
    }
    cnt++;
    for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
        for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
            setPixel(stretchedSurface.get(), j, i, colorU32(0x10, 0xBB, 0x10));
        }
    }
    cnt++;
    for (int j = 100 * cnt; j < 100 * (cnt + 1); ++j) {
        for (int i = 100 * cnt; i < 100 * (cnt + 1); ++i) {
            setPixel(stretchedSurface.get(), j, i, colorU32(0x10, 0x10, 0xBB));
        }
    }

    //Event handler
    SDL_Event e;
    //While application is running
    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    stretchRect.w = e.window.data1;
                    stretchRect.h = e.window.data2;
                    screenSurface = SDL_GetWindowSurface(window.get());
                }
            }
        }

        //Apply the image stretched
        SDL_BlitScaled(stretchedSurface.get(), NULL, screenSurface, &stretchRect);

        //Update the surface
        SDL_UpdateWindowSurface(window.get());
    }

    SDL_Quit();

    return 0;
}
