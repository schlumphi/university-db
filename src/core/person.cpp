#include "person.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>

#include "helpers/bytes/tokenize.hpp"
#include "helpers/predicates/string_checks.hpp"
#include "helpers/random/personal_data.hpp"

Person::Person(
    const std::string& first_name,
    const std::string& last_name,
    const Address& address,
    const Pesel& pesel,
    const Gender gender) : m_first_name(validate_name(first_name)),
                           m_last_name(validate_name(last_name)),
                           m_address(address),
                           m_pesel(pesel),
                           m_gender(validate_gender(pesel, gender)) {}

std::string Person::validate_name(const std::string& name) {
    const auto name_chunks = bytes::tokenize(name, '-');
    for (const auto name_chunk : name_chunks) {
        if (name_chunk.empty()) {
            throw std::invalid_argument("name chunk cannot be empty");
        }
        if (name_chunk.size() < 2) {
            throw std::invalid_argument("expected name chunk to be at least 2 character length");
        }
        if (!predicates::is_capitalized_alpha(name_chunk)) {
            throw std::invalid_argument("name chunk must be capitalized string");
        }
    }

    return name;
}

Gender Person::validate_gender(const Pesel& pesel, const Gender gender) {
    if (pesel.gender() != gender && gender != Gender::Unspecified) {
        throw std::invalid_argument("invalid gender for provided pesel num");
    }
    return gender;
}

std::vector<std::string> Person::tokenize() noexcept {
    std::vector<std::string> tokens(8);
    tokens[0] = m_first_name;
    tokens[1] = m_last_name;
    tokens[2] = m_address.street();
    tokens[3] = m_address.apartment();
    tokens[4] = m_address.postal_code().value();
    tokens[5] = m_address.city();
    tokens[6] = m_pesel.value();
    tokens[7] = parse_gender(m_gender);

    return tokens;
}

Person Person::random_person() {
    const auto gender = pseudorandom::personal_data::random_gender();

    return Person{
        pseudorandom::personal_data::random_name(gender),
        pseudorandom::personal_data::random_surname(gender),
        pseudorandom::personal_data::random_address(),
        pseudorandom::personal_data::random_pesel(gender),
        gender};
}
