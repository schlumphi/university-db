#pragma once

#include <iostream>
#include <random>

namespace pseudorandom {

inline std::random_device random_device;
inline std::mt19937_64 generator(random_device());

inline uint64_t random_uint64() {
    return static_cast<uint64_t>(generator());
}

inline uint32_t random_uint32() {
    return static_cast<uint32_t>(generator());
}

}  // namespace pseudorandom
