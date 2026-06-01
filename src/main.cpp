#include <iostream>

#include "helpers/random/personal_data.hpp"

int main() {
    std::cout << pseudorandom::personal_data::random_pesel().value() << "\n";
    std::cout << pseudorandom::personal_data::random_name() << "\n";

    const auto address = pseudorandom::personal_data::random_address();
    std::cout << address.street() << " " << address.apartment() << "\n";
    std::cout << address.postal_code().value() << " " << address.city() << "\n";

    return 0;
}
