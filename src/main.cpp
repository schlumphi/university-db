#include <iostream>

#include "core/database.hpp"
#include "core/employee.hpp"
#include "helpers/random/personal_data.hpp"

int main() {
    std::cout << pseudorandom::personal_data::random_pesel().value() << "\n";
    std::cout << pseudorandom::personal_data::random_name() << "\n";

    const auto address = pseudorandom::personal_data::random_address();
    std::cout << address.street() << " " << address.apartment() << "\n";
    std::cout << address.postal_code().value() << " " << address.city() << "\n";

    const auto employee = Employee::random_employee();
    std::cout << employee.first_name() << "\n";

    auto db = Database();
    db.fill_with_random_data(10);
    db.sort_by_name();
    std::cout << db.display();

    return 0;
}
