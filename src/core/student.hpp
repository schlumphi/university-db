#pragma once
#include <cstdint>
#include <string>
#include <string_view>
#include "helpers/address.hpp"
#include "helpers/gender.hpp"
#include "helpers/pesel.hpp"

auto parse_student_error_code(Student::ErrorCode error) -> std::string_view;

class Student {
public:
    enum class ErrorCode {
        Ok,
        EmptyFirstName,
        EmptyLastName,
        NameDoesntBeginWithUppercase
    };

    Student(
        const std::string& first_name,
        const std::string& last_name,
        const Address& address,
        const Pesel& pesel,
        const uint64_t index_num,
        const Gender gender);

    auto first_name() const noexcept -> const std::string& { return m_first_name; }
    auto last_name() const noexcept -> const std::string& { return m_last_name; }
    auto address() const noexcept -> const Address& { return m_address; }
    auto pesel() const noexcept -> const Pesel& { return m_pesel; }
    auto index_num() const noexcept -> const uint64_t { return m_index_num; }
    auto gender() const noexcept -> const Gender { return m_gender; }

private:
    const std::string m_first_name;
    const std::string m_last_name;
    const Address m_address;
    const Pesel m_pesel;
    const uint64_t m_index_num;
    const Gender m_gender;

    static auto validate_first_name(const std::string& first_name) noexcept -> ErrorCode;
};
