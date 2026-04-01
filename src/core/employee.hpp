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

protected:
    void set_salary(const uint64_t salary) { m_salary = salary; }

    uint64_t m_salary;

    friend class Database;
};
