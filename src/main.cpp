#include <iostream>

#include "helpers/random/pseudorandom.hpp"

int main() {
    std::cout << pseudorandom::random_uint32() << "\n";
    return 0;
}
