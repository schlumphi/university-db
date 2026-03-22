#pragma once
#include <cstdint>
#include <optional>
#include <string>

#include "helpers/address.hpp"
#include "helpers/gender.hpp"
#include "helpers/pesel.hpp"

class Database;

class Student {
public:
    Student(
        const std::string& first_name,
        const std::string& last_name,
        const Address& address,
        const Pesel& pesel,
        const Gender gender);

    bool operator==(const Student& other) const noexcept {
        if (other.pesel().value() == m_pesel.value()) {
            return true;
        }
        return false;
    }

    const std::string& first_name() const noexcept { return m_first_name; }
    const std::string& last_name() const noexcept { return m_last_name; }
    const Address& address() const noexcept { return m_address; }
    const Pesel& pesel() const noexcept { return m_pesel; }
    uint64_t index_num() const noexcept { return m_index_num; }
    Gender gender() const noexcept { return m_gender; }

    static std::string validate_name(const std::string& name);
    static Gender validate_gender(const Pesel& pesel, const Gender gender);

private:
    void set_index_num(const uint64_t index_num) {
        if (index_num != 0ULL && m_index_num == 0ULL) {
            m_index_num = index_num;
        }
    }

    const std::string m_first_name;
    const std::string m_last_name;
    const Address m_address;
    const Pesel m_pesel;
    uint64_t m_index_num;
    const Gender m_gender;

    friend class Database;
};
