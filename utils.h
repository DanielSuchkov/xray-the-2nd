#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <cstdint>

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

inline uint32_t colorU32(uint32_t r, uint32_t g, uint32_t b) {
    return (r << 16) | (g << 8) | b;
}
