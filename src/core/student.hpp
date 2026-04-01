#pragma once
#include <cstdint>
#include <optional>
#include <string>

#include "helpers/address.hpp"
#include "helpers/gender.hpp"
#include "helpers/pesel.hpp"
#include "person.hpp"

class Database;

class Student : public Person {
public:
    Student(
        const std::string& first_name,
        const std::string& last_name,
        const Address& address,
        const Pesel& pesel,
        const Gender gender) : Person(first_name, last_name, address, pesel, gender), m_index_num(0ULL) {}

    uint64_t index_num() const noexcept { return m_index_num; }

private:
    void set_index_num(const uint64_t index_num) {
        if (index_num != 0ULL && m_index_num == 0ULL) {
            m_index_num = index_num;
        }
    }

    uint64_t m_index_num;

    friend class Database;
};
