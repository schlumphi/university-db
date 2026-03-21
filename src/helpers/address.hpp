#pragma once
#include <optional>
#include <string>

#include "postal_code.hpp"

class Address {
public:
    enum class ErrorCode {
        StreetNameEmpty,
        StreetNameInvalidFormat,
        StreetNameInvalidNameFormat,
        StreetInvalidNumberFormat,
        ApartmentInvalidCharacters,
        CityNameChunkTooShort,
        CityNameDoesntStartWithCapitalLetter,
        CityNameInvalidCharacters,
        CityNameChunkContainsInnerUpperCaseLetter
    };

    Address(
        const std::string& street,
        const std::string& apartment,
        const PostalCode& postal_code,
        const std::string& city);

    auto street() const noexcept -> const std::string& { return m_street; }
    auto apartment() const noexcept -> const std::string& { return m_apartment; }
    auto postal_code() const noexcept -> const PostalCode& { return m_postal_code; }
    auto city() const noexcept -> const std::string& { return m_city; }

    // FIXME: validate positively names with polish letters like ą, ę...
    static auto validate_street(const std::string& code) noexcept -> std::optional<ErrorCode>;
    static auto validate_apartment(const std::string& apartment) noexcept -> std::optional<ErrorCode>;
    static auto validate_city(const std::string& city) noexcept -> std::optional<ErrorCode>;

private:
    const std::string m_street;
    const std::string m_apartment;
    const PostalCode m_postal_code;
    const std::string m_city;
};

auto parse_address_error_code(Address::ErrorCode error) -> std::string_view;
