#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include "helpers/address.hpp"
#include "helpers/gender.hpp"
#include "helpers/pesel.hpp"

class Student {
public:
    enum class ErrorCode {
        EmptyFirstName,
        EmptyLastName,
        NameDoesntBeginWithUppercase
    };

    Student(
        const std::string& first_name,
        const std::string& last_name,
        const Address& address,
        const uint64_t index_num,
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

    static auto validate_first_name(const std::string& first_name) noexcept -> std::optional<ErrorCode>;

private:
    const std::string m_first_name;
    const std::string m_last_name;
    const Address m_address;
    const Pesel m_pesel;
    const uint64_t m_index_num;
    const Gender m_gender;
};

auto parse_student_error_code(Student::ErrorCode error) -> std::string_view;
