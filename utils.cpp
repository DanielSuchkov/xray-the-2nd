#include "utils.h"
#include <thread>
#include <atomic>

float thread_rng_f32() {
    static std::atomic_uint tid(0);
    static thread_local std::mt19937 rng(tid.fetch_add(1));
    static thread_local std::uniform_real_distribution<float> distr {0.0f, 1.0f};
    return distr(rng);
}
