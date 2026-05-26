#pragma once
#include "person.hpp"

class Database;

class Employee : public Person {
public:
    Employee(const std::string& first_name,
             const std::string& last_name,
             const Address& address,
             const Pesel& pesel,
             const Gender gender) : Person(first_name, last_name, address, pesel, gender), m_salary{0ULL} {}

    uint64_t salary() const noexcept { return m_salary; }

    std::array<std::string, 10> tokenize() noexcept override {
        std::array<std::string, 10> tokens;
        tokens[0] = m_first_name;
        tokens[1] = m_last_name;
        tokens[2] = m_address.street();
        tokens[3] = m_address.apartment();
        tokens[4] = m_address.postal_code().value();
        tokens[5] = m_address.city();
        tokens[6] = "";
        tokens[7] = m_pesel.value();
        tokens[8] = parse_gender(m_gender);
        tokens[9] = std::to_string(m_salary);

        return tokens;
    }

private:
    void set_salary(const uint64_t salary) { m_salary = salary; }

    uint64_t m_salary;

    friend class Database;
};
