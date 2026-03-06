#include "address.hpp"
#include <algorithm>
#include <cctype>

Address::Address(
    const std::string& street,
    const std::string& apartment,
    const PostalCode& postal_code,
    const std::string& city)
    : m_street(street), m_apartment(apartment), m_postal_code(postal_code), m_city(city) {
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

auto parse_address_error_code(Address::ErrorCode error) -> std::string_view {
    switch (error) {
    default:
        return "Ok";
    }
}
