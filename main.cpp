#include <string>
#include <iostream>
#include <memory>
#include <cstdint>
#include <cstdio>
#include <cassert>
#include <SDL2/SDL.h>
#include "glm/glm.hpp"
#include "utils.h"
#include "framebuffer.h"
#include "renderer.h"


int runApp(int, char*[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    const bool draw_centered = true;
    const int SCREEN_WIDTH = 300;
    const int SCREEN_HEIGHT = 300;

    SdlWindowUptr window = get_unique_ptr(
                               SDL_CreateWindow(
                                   "x-ray the 2nd",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH,
                                   SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN),
                               SDL_DestroyWindow
                               );
    if (window == nullptr) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window.get());

    Renderer r;
    ScreenBufferRGB drawableSurface(SCREEN_WIDTH, SCREEN_HEIGHT);
    FramebufferRGB fb(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!drawableSurface) {
        printf("Failed to create surface!\n");
        return 1;
    }
    bool quit = false;

    SDL_Rect viewRect;
    viewRect.x = 0;
    viewRect.y = 0;
    viewRect.w = SCREEN_WIDTH;
    viewRect.h = SCREEN_HEIGHT;

    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    if (draw_centered) {
                        viewRect.x = std::max(e.window.data1/2 - viewRect.w/2, 0);
                        viewRect.y = std::max(e.window.data2/2 - viewRect.h/2, 0);
                    }
                    screenSurface = SDL_GetWindowSurface(window.get());
                }
            }
        }

        r.draw(fb);
        fb.fillScreenBuffer(drawableSurface);
        SDL_UpperBlit(drawableSurface.getSdlSurface(), nullptr, screenSurface, &viewRect);
        SDL_UpdateWindowSurface(window.get());
    }

    SDL_Quit();
    return 0;
}

#ifndef RUN_TESTS
int main(int argc, char* argv[]) {
    return runApp(argc, argv);
}
#else
#include "tests/geometry.h"

#include <gtest/gtest.h>
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
