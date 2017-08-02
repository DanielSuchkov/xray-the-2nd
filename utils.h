#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <cstdint>
#include <algorithm>
#define GLM_FORCE_NO_CTOR_INIT
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

using glm::vec2;
using glm::vec3;
using glm::vec4;

inline uint32_t color_u32(uint32_t r, uint32_t g, uint32_t b) {
    return (r << 16) | (g << 8) | b;
}

inline uint32_t f32_to_byte(float f) {
    return uint32_t(std::min(f * 255.0f, 255.0f));
}

inline uint32_t color_to_u32(const vec3& c) {
    return color_u32(f32_to_byte(c.r), f32_to_byte(c.g), f32_to_byte(c.b));
}

float thread_rng_f32();
