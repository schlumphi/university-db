#pragma once
#include <optional>
#include <string>

#include "postal_code.hpp"

class Address {
public:
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
    // FIXME: better validator function atomization
    static std::string validate_street(const std::string& street);
    static std::string validate_apartment(const std::string& apartment);
    static std::string validate_city(const std::string& city);

private:
    static void validate_street_name_chunk(std::string_view name_chunk);
    static void validate_street_name_alpha_chunk(std::string_view chunk);
    static void validate_street_name_digit_chunk(std::string_view chunk);
    static void validate_street_number(std::string_view street_number);

    const std::string m_street;
    const std::string m_apartment;
    const PostalCode m_postal_code;
    const std::string m_city;
};
