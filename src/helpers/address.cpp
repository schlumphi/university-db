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

    auto tokens = bytes::tokenize(code, ' ');
    if (tokens.size() < 2) {
        return ErrorCode::StreetNameInvalidFormat;
    }

    auto st_name = tokens.front();
    if (std::any_of(st_name.begin(), st_name.end(), [](char c) { return !std::isalnum(c); })) {
        return ErrorCode::StreetNameInvalidNameFormat;
    }

    auto st_num = tokens.back();
    if (std::any_of(st_num.begin(), st_num.end(), [](char c) { return !std::isalnum(c); })) {
        return ErrorCode::StreetInvalidNumberFormat;
    }

    if (!std::isdigit(st_num.front())) {
        return ErrorCode::StreetInvalidNumberFormat;
    }

    auto alpha_encountered = false;
    for (auto c : st_num) {
        if (!alpha_encountered && std::isalpha(c)) {
            alpha_encountered = true;
        }
        if (std::isdigit(c) && alpha_encountered) {
            return ErrorCode::StreetInvalidNumberFormat;
        }
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
    auto city_name_space_chunks = bytes::tokenize(city, ' ');
    for (const auto name_space_chunk : city_name_space_chunks) {
        auto city_name_hyphen_chunks = bytes::tokenize(name_space_chunk, '-');
        for (auto name_hyphen_chunk : city_name_hyphen_chunks) {
            if (name_hyphen_chunk.size() < 2) {
                return ErrorCode::CityNameChunkTooShort;
            }
            if (!std::isupper(name_hyphen_chunk.front())) {
                return ErrorCode::CityNameDoesntStartWithCapitalLetter;
            }
            if (std::any_of(
                    name_hyphen_chunk.begin(),
                    name_hyphen_chunk.end(),
                    [](char c) { return !std::isalpha(c); })) {
                return ErrorCode::CityNameInvalidCharacters;
            }
            auto inner_name_hyphen_chunk = name_hyphen_chunk.substr(1);
            if (std::any_of(
                    inner_name_hyphen_chunk.begin(),
                    inner_name_hyphen_chunk.end(),
                    [](char c) { return std::isupper(c); })) {
                return ErrorCode::CityNameChunkContainsInnerUpperCaseLetter;
            }
        }
    }

    return std::nullopt;
}

auto parse_address_error_code(Address::ErrorCode error) -> std::string_view {
    switch (error) {
    case Address::ErrorCode::StreetNameEmpty:
        return "expected non-empty street name";
    case Address::ErrorCode::StreetNameInvalidFormat:
        return "expected street format: 'name [name] alphanum' e.g. Warszawska 43F";
    case Address::ErrorCode::StreetNameInvalidNameFormat:
        return "expected street name chunks to be alphanum, e.g. ul. 3 Maja, Batalionów Chłopskich";
    case Address::ErrorCode::StreetInvalidNumberFormat:
        return "street number must have the form: NUM[NUM][ALPHA]";
    case Address::ErrorCode::ApartmentInvalidCharacters:
        return "expected apartment in alpahunmerical format e.g. 21/37, 42";
    case Address::ErrorCode::CityNameChunkTooShort:
        return "city name chunk must be at least 2 characters length";
    case Address::ErrorCode::CityNameDoesntStartWithCapitalLetter:
        return "city name must start with capital letter";
    case Address::ErrorCode::CityNameInvalidCharacters:
        return "expected city name to contain only alphabetic characters";
    case Address::ErrorCode::CityNameChunkContainsInnerUpperCaseLetter:
        return "city name chunks cannot contain uppercase letters except fist one";
    default:
        return "Ok";
    }
}
