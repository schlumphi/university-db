#include "address.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>

#include "helpers/bytes/tokenize.hpp"

Address::Address(
    const std::string& street,
    const std::string& apartment,
    const PostalCode& postal_code,
    const std::string& city)
    : m_street(validate_street(street)), m_apartment(validate_apartment(apartment)), m_postal_code(postal_code), m_city(validate_city(city)) {}

// FIXME: better validation with tokenize
// FIXME: disperse into smaller private methods
// BUG: ut failure
std::string Address::validate_street(const std::string& street) {
    if (street.empty()) {
        throw std::invalid_argument("expected non-empty street name");
    }

    auto tokens = bytes::tokenize(street, ' ');
    if (tokens.size() < 2) {
        throw std::invalid_argument("expected street format: 'name [name] alphanum' e.g. Warszawska 43F");
    }

    auto st_name = tokens.front();
    if (std::any_of(st_name.begin(), st_name.end(), [](char c) { return !std::isalnum(c); })) {
        throw std::invalid_argument(
            "expected street name chunks to be alphanum, e.g. ul. 3 Maja, Batalionów Chłopskich");
    }

    auto st_num = tokens.back();
    if (std::any_of(st_num.begin(), st_num.end(), [](char c) { return !std::isalnum(c); })) {
        throw std::invalid_argument("street number must have the form: NUM[NUM][ALPHA]");
    }

    if (!std::isdigit(st_num.front())) {
        throw std::invalid_argument("street number must have the form: NUM[NUM][ALPHA]");
    }

    auto alpha_encountered = false;
    for (auto c : st_num) {
        if (!alpha_encountered && std::isalpha(c)) {
            alpha_encountered = true;
        }
        if (std::isdigit(c) && alpha_encountered) {
            throw std::invalid_argument("street number must have the form: NUM[NUM][ALPHA]");
        }
    }

    return street;
}

// FIXME: disperse into smaller private methods
std::string Address::validate_apartment(const std::string& apartment) {
    if (apartment.empty()) {
        return apartment;
    }

    if (std::all_of(
            apartment.begin(),
            apartment.end(),
            [](char c) { return std::isalnum(c) || c == '/'; })) {
        if (apartment.starts_with('/') || apartment.ends_with('/')) {
            throw std::invalid_argument("expected apartment in alpahunmerical format e.g. 21/37, 42");
        } else {
            return apartment;
        }
    } else {
        throw std::invalid_argument("expected apartment in alpahunmerical format e.g. 21/37, 42");
    }
}

// FIXME: disperse into smaller private methods
std::string Address::validate_city(const std::string& city) {
    auto city_name_space_chunks = bytes::tokenize(city, ' ');
    for (const auto name_space_chunk : city_name_space_chunks) {
        auto city_name_hyphen_chunks = bytes::tokenize(name_space_chunk, '-');
        for (auto name_hyphen_chunk : city_name_hyphen_chunks) {
            if (name_hyphen_chunk.size() < 2) {
                throw std::invalid_argument("city name chunk must be at least 2 characters length");
            }
            if (!std::isupper(name_hyphen_chunk.front())) {
                throw std::invalid_argument("city name chunk must start with capital letter");
            }
            if (std::any_of(
                    name_hyphen_chunk.begin(),
                    name_hyphen_chunk.end(),
                    [](char c) { return !std::isalpha(c); })) {
                throw std::invalid_argument("expected city name chunk to contain only alphabetic characters");
            }
            auto inner_name_hyphen_chunk = name_hyphen_chunk.substr(1);
            if (std::any_of(
                    inner_name_hyphen_chunk.begin(),
                    inner_name_hyphen_chunk.end(),
                    [](char c) { return std::isupper(c); })) {
                throw std::invalid_argument("city name chunks cannot contain uppercase letters except fist one");
            }
        }
    }

    return city;
}
