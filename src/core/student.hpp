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

    std::array<std::string, 10> tokenize() noexcept override {
        std::array<std::string, 10> tokens;
        tokens[0] = m_first_name;
        tokens[1] = m_last_name;
        tokens[2] = m_address.street();
        tokens[3] = m_address.apartment();
        tokens[4] = m_address.postal_code().value();
        tokens[5] = m_address.city();
        tokens[6] = std::to_string(m_index_num);
        tokens[7] = m_pesel.value();
        tokens[8] = parse_gender(m_gender);
        tokens[9] = "";

        return tokens;
    }

private:
    void set_index_num(const uint64_t index_num) {
        if (index_num != 0ULL && m_index_num == 0ULL) {
            m_index_num = index_num;
        }
    }

    uint64_t m_index_num;

    friend class Database;
};
