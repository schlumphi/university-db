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

    const std::string& street() const noexcept { return m_street; }
    const std::string& apartment() const noexcept { return m_apartment; }
    const PostalCode& postal_code() const noexcept { return m_postal_code; }
    const std::string& city() const noexcept { return m_city; }

    // FIXME: validate positively names with polish letters like ą, ę...
    static std::optional<ErrorCode> validate_street(const std::string& code) noexcept;
    static std::optional<ErrorCode> validate_apartment(const std::string& apartment) noexcept;
    static std::optional<ErrorCode> validate_city(const std::string& city) noexcept;

private:
    const std::string m_street;
    const std::string m_apartment;
    const PostalCode m_postal_code;
    const std::string m_city;
};

std::string_view parse_address_error_code(Address::ErrorCode error);
