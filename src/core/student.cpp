#include "student.hpp"
#include <cctype>
#include <iostream>

auto parse_student_error_code(Student::ErrorCode error) -> std::string_view {
    switch (error) {
    case Student::ErrorCode::EmptyFirstName:
        return "first name cannot be empty";
    case Student::ErrorCode::EmptyLastName:
        return "last name cannot be empty";
    case Student::ErrorCode::NameDoesntBeginWithUppercase:
        return "name must begin with capital letter";
    default:
        return "Ok";
    }
}

Student::Student(
    const std::string& first_name,
    const std::string& last_name,
    const Address& address,
    const Pesel& pesel,
    const uint64_t index_num,
    const Gender gender) : m_first_name(first_name),
                           m_last_name(last_name),
                           m_address(address),
                           m_pesel(pesel),
                           m_index_num(index_num),
                           m_gender(gender) {
    // if (first_name.empty()) {
    //     throw std::invalid_argument("Student::Student: 'first_name' acannot be empty.");
    // }
    // if (last_name.empty()) {
    //     throw std::invalid_argument("Student::Student: 'last_name' acannot be empty.");
    // }
    // if (!std::isupper(first_name[0])) {
    //     throw std::invalid_argument("Student::Student: 'first_name' acannot be empty.");
    // }
}
