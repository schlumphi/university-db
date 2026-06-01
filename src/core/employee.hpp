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

    Employee(const Person& person) : Person(person), m_salary{0ULL} {}

    uint64_t salary() const noexcept { return m_salary; }

    std::vector<std::string> tokenize() noexcept override {
        auto tokens = Person::tokenize();
        tokens.push_back("");
        tokens.push_back(std::to_string(m_salary));

        return tokens;
    }

    static Employee random_employee() {
        return Employee{Person::random_person()};
    }

private:
    void set_salary(const uint64_t salary) { m_salary = salary; }

    uint64_t m_salary;

    friend class Database;
};
