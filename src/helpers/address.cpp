#include "address.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

Address::Address(
    const std::string& street,
    const std::string& apartment,
    const PostalCode& postal_code,
    const std::string& city)
    : m_street(street), m_apartment(apartment), m_postal_code(postal_code), m_city(city) {
    if (auto error = validate_street(street)) {
        throw std::invalid_argument(std::string{parse_address_error_code(*error)});
    }

    if (auto error = validate_apartment(apartment)) {
        throw std::invalid_argument(std::string{parse_address_error_code(*error)});
    }

    if (auto error = validate_city(city)) {
        throw std::invalid_argument(std::string{parse_address_error_code(*error)});
    }
}

auto Address::validate_street(const std::string& code) noexcept -> std::optional<Address::ErrorCode> {
    if (code.empty()) {
        return ErrorCode::StreetNameEmpty;
    }
    return std::nullopt;
}

auto Address::validate_apartment(const std::string& apartment) noexcept -> std::optional<Address::ErrorCode> {
    if (apartment.empty()) {
        return std::nullopt;
    }

    if (std::all_of(
            apartment.begin(),
            apartment.end(),
            [](char c) { return std::isalnum(c) || c == '/'; })) {
        if (apartment.starts_with('/') || apartment.ends_with('/')) {
            return ErrorCode::ApartmentInvalidCharacters;
        } else {
            return std::nullopt;
        }

    } else {
        return ErrorCode::ApartmentInvalidCharacters;
    }
}

auto Address::validate_city(const std::string& city) noexcept -> std::optional<Address::ErrorCode> {
    if (city.length() < 2) {
        return ErrorCode::CityNameTooShort;
    }
    if (std::any_of(
            city.begin(),
            city.end(),
            [](char c) { return !std::isalpha(c); })) {
        return ErrorCode::CityNameInvalidCharacters;
    }
    if (!std::isupper(city.front())) {
        return ErrorCode::CityNameDoesntStartWithCapitalLetter;
    }
    return std::nullopt;
}

auto parse_address_error_code(Address::ErrorCode error) -> std::string_view {
    switch (error) {
    case Address::ErrorCode::StreetNameEmpty:
        return "expected non-empty street name";
    case Address::ErrorCode::ApartmentInvalidCharacters:
        return "expected apartment in alpahunmerical format e.g. 21/37, 42";
    case Address::ErrorCode::CityNameTooShort:
        return "city name must be at least 2 characters length";
    case Address::ErrorCode::CityNameDoesntStartWithCapitalLetter:
        return "city name must start with capital letter";
    case Address::ErrorCode::CityNameInvalidCharacters:
        return "expected city name to contain only alphabetic characters";
    default:
        return "Ok";
    }
}
