#pragma once

#include <iostream>
#include <random>

namespace pseudorandom {

inline std::random_device random_device;
inline std::mt19937_64 generator(random_device());

inline uint64_t random_uint64(const uint64_t min = 0ULL, const uint64_t max = std::numeric_limits<uint64_t>::max() - 1ULL) {
    if (min > max) {
        throw std::runtime_error("expected 'min' <= 'max'");
    }
    return min + (static_cast<uint64_t>(generator()) % (max - min + 1ULL));
}

inline uint32_t random_uint32(const uint32_t min = 0U, const uint32_t max = std::numeric_limits<uint32_t>::max() - 1U) {
    if (min > max) {
        throw std::runtime_error("expected 'min' <= 'max'");
    }
    return min + (static_cast<uint32_t>(generator()) % (max - min + 1U));
}

}  // namespace pseudorandom
