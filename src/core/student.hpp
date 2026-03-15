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
    enum class ErrorCode {
        EmptyName,
        NameDoesntBeginWithUppercase,
        NameContainsUppercaseCharacters,
        NameContainsInvalidCharacters,
    };

    Student(
        const std::string& first_name,
        const std::string& last_name,
        const Address& address,
        const Pesel& pesel,
        const Gender gender);

    auto operator==(const Student& other) -> bool {
        if (other.pesel().value() == m_pesel.value()) {
            return true;
        }
        return false;
    }

    auto first_name() const noexcept -> const std::string& { return m_first_name; }
    auto last_name() const noexcept -> const std::string& { return m_last_name; }
    auto address() const noexcept -> const Address& { return m_address; }
    auto pesel() const noexcept -> const Pesel& { return m_pesel; }
    auto index_num() const noexcept -> const uint64_t { return m_index_num; }
    auto gender() const noexcept -> const Gender { return m_gender; }

    static auto validate_name(const std::string& name) noexcept -> std::optional<ErrorCode>;

private:
    auto set_index_num(const uint64_t index_num) -> void {
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

auto parse_student_error_code(Student::ErrorCode error) -> std::string_view;
