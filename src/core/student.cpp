#include "student.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

Student::Student(
    const std::string& first_name,
    const std::string& last_name,
    const Address& address,
    const Pesel& pesel,
    const Gender gender) : m_first_name(first_name),
                           m_last_name(last_name),
                           m_address(address),
                           m_pesel(pesel),
                           m_index_num(0ULL),
                           m_gender(gender) {
    if (auto error = validate_name(first_name)) {
        throw std::invalid_argument(std::string(parse_student_error_code(*error)));
    }
    if (auto error = validate_name(last_name)) {
        throw std::invalid_argument(std::string(parse_student_error_code(*error)));
    }
    if (auto error = validate_gender(pesel, gender)) {
        throw std::invalid_argument(std::string(parse_student_error_code(*error)));
    }
}

auto Student::validate_name(const std::string& name) noexcept -> std::optional<Student::ErrorCode> {
    if (name.empty()) {
        return ErrorCode::EmptyName;
    }
    if (std::any_of(name.begin(), name.end(), [](char c) { return !std::isalpha(c); })) {
        return ErrorCode::NameContainsInvalidCharacters;
    }
    if (!std::isupper(name.front())) {
        return ErrorCode::NameDoesntBeginWithUppercase;
    }
    if (std::any_of(name.begin() + 1, name.end(), [](char c) { return std::isupper(c); })) {
        return ErrorCode::NameContainsUppercaseCharacters;
    }
    return std::nullopt;
}

auto Student::validate_gender(const Pesel& pesel, const Gender gender) noexcept -> std::optional<Student::ErrorCode> {
    if (pesel.gender() != gender) {
        return ErrorCode::GenderPeselMismatch;
    }
    return std::nullopt;
}

auto parse_student_error_code(Student::ErrorCode error) -> std::string_view {
    switch (error) {
    case Student::ErrorCode::EmptyName:
        return "name cannot be empty";
    case Student::ErrorCode::NameDoesntBeginWithUppercase:
        return "name must begin with capital letter";
    case Student::ErrorCode::NameContainsInvalidCharacters:
        return "name must contain only alpha letters";
    case Student::ErrorCode::NameContainsUppercaseCharacters:
        return "uppercase character is only available at the beggining of the name";
    case Student::ErrorCode::GenderPeselMismatch:
        return "invalid gender for provided pesel num";
    default:
        return "Ok";
    }
}
