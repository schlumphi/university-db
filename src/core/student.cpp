#include "student.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>

#include "helpers/bytes/tokenize.hpp"

Student::Student(
    const std::string& first_name,
    const std::string& last_name,
    const Address& address,
    const Pesel& pesel,
    const Gender gender) : m_first_name(validate_name(first_name)),
                           m_last_name(validate_name(last_name)),
                           m_address(address),
                           m_pesel(pesel),
                           m_index_num(0ULL),
                           m_gender(validate_gender(pesel, gender)) {}

std::string Student::validate_name(const std::string& name) {
    const auto name_chunks = bytes::tokenize(name, '-');
    for (const auto name_chunk : name_chunks) {
        if (name_chunk.empty()) {
            throw std::invalid_argument("name chunk cannot be empty");
        }
        if (name_chunk.size() < 2) {
            throw std::invalid_argument("expected name chunk to be at least 2 character length");
        }
        if (std::any_of(name_chunk.begin(), name_chunk.end(), [](char c) { return !std::isalpha(c); })) {
            throw std::invalid_argument("name chunk must contain only alpha letters");
        }
        if (!std::isupper(name_chunk.front())) {
            throw std::invalid_argument("name chunk must begin with capital letter");
        }
        if (std::any_of(name_chunk.begin() + 1, name_chunk.end(), [](char c) { return std::isupper(c); })) {
            throw std::invalid_argument("uppercase character is only available at the beggining of the name chunk");
        }
    }

    return name;
}

Gender Student::validate_gender(const Pesel& pesel, const Gender gender) {
    if (pesel.gender() != gender) {
        throw std::invalid_argument("invalid gender for provided pesel num");
    }
    return gender;
}
