#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <cstdint>
#include <algorithm>
#include "glm/glm.hpp"

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

using glm::vec3;
using glm::vec4;

inline uint32_t colorU32(uint32_t r, uint32_t g, uint32_t b) {
    return (r << 16) | (g << 8) | b;
}

inline uint32_t f32ToByte(float f) {
    return uint32_t(std::min(f * 255.0f, 255.0f));
}

inline uint32_t colorToU32(const vec3& c) {
    return colorU32(f32ToByte(c.r), f32ToByte(c.g), f32ToByte(c.b));
}
