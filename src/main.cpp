#include <iostream>

#include "helpers/random/personal_data.hpp"

int main() {
    std::cout << pseudorandom::personal_data::random_pesel().value() << "\n";
    return 0;
}
