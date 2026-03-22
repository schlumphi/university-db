#include "address.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>

#include "helpers/bytes/tokenize.hpp"
#include "predicates/string_checks.hpp"

Address::Address(
    const std::string& street,
    const std::string& apartment,
    const PostalCode& postal_code,
    const std::string& city)
    : m_street(validate_street(street)), m_apartment(validate_apartment(apartment)), m_postal_code(postal_code), m_city(validate_city(city)) {}

std::string Address::validate_street(const std::string& street) {
    if (street.empty()) {
        throw std::invalid_argument("expected non-empty street name");
    }

    auto tokens = bytes::tokenize(street, ' ');
    if (tokens.size() < 2) {
        throw std::invalid_argument("expected street format: 'name [name] alphanum' e.g. Warszawska 43F");
    }

    auto street_number = tokens.back();
    validate_street_number(street_number);
    tokens.pop_back();

    for (auto street_name_space_chunk : tokens) {
        auto street_name_hyphen_tokens = bytes::tokenize(street_name_space_chunk, '-');
        for (auto street_name_hyphen_chunk : street_name_hyphen_tokens) {
            validate_street_name_chunk(street_name_hyphen_chunk);
        }
    }

    return street;
}

void Address::validate_street_name_chunk(std::string_view name_chunk) {
    if (name_chunk.empty()) {
        throw std::invalid_argument("expected non-empty street name chunk");
    }

    if (std::isalpha(name_chunk.front())) {
        validate_street_name_alpha_chunk(name_chunk);
    } else if (std::isdigit(name_chunk.front())) {
        validate_street_name_digit_chunk(name_chunk);
    } else {
        throw std::invalid_argument("encountered unexpected character in street name chunk (expected alphanum characters)");
    }
}

void Address::validate_street_name_alpha_chunk(std::string_view chunk) {
    if (!predicates::is_capitalized_alpha(chunk)) {
        throw std::invalid_argument(
            "street name alphabetic chunk must contain lowercase letter and start with capital letter");
    }
}

void Address::validate_street_name_digit_chunk(std::string_view chunk) {
    if (!predicates::contains_only_digits(chunk)) {
        throw std::invalid_argument(
            "street name digit chunk must contain only number characters");
    }
}

void Address::validate_street_number(std::string_view street_number) {
    if (!predicates::contains_only_alphanum(street_number)) {
        throw std::invalid_argument("street number must have the form: NUM[NUM][ALPHA]");
    }

    if (!std::isdigit(street_number.front())) {
        throw std::invalid_argument("street number must have the form: NUM[NUM][ALPHA]");
    }

    auto alpha_encountered = false;
    for (auto c : street_number) {
        if (!alpha_encountered && std::isalpha(c)) {
            alpha_encountered = true;
        }
        if (std::isdigit(c) && alpha_encountered) {
            throw std::invalid_argument("street number must have the form: NUM[NUM][ALPHA]");
        }
    }
}

std::string Address::validate_apartment(const std::string& apartment) {
    if (apartment.empty()) {
        return apartment;
    }

    auto tokens = bytes::tokenize(apartment, '/');
    for (auto apartment_chunk : tokens) {
        if (!predicates::contains_only_alphanum(apartment_chunk)) {
            throw std::invalid_argument("expected apartment chunk in alphanumerical format e.g. 21/37, 42");
        }
    }
    return apartment;
}

std::string Address::validate_city(const std::string& city) {
    auto city_name_space_chunks = bytes::tokenize(city, ' ');
    for (const auto name_space_chunk : city_name_space_chunks) {
        auto city_name_hyphen_chunks = bytes::tokenize(name_space_chunk, '-');
        for (auto name_hyphen_chunk : city_name_hyphen_chunks) {
            validate_city_name_chunk(name_hyphen_chunk);
        }
    }

    return city;
}

void Address::validate_city_name_chunk(std::string_view chunk) {
    if (chunk.size() < 2) {
        throw std::invalid_argument("city name chunk must be at least 2 characters length");
    }
    if (!predicates::is_capitalized_alpha(chunk)) {
        throw std::invalid_argument("city name chunk must be capitalized alphabetic string");
    }
}
