#pragma once
#include <string>
#include <string_view>
#include "postal_code.hpp"

class Address {
public:
    Address(
        std::string_view street,
        std::string_view apartment,
        const PostalCode& postal_code,
        std::string_view city);

    auto street() const noexcept -> const std::string& { return m_street; }
    auto apartment() const noexcept -> const std::string& { return m_apartment; }
    auto postal_code() const noexcept -> const PostalCode& { return m_postal_code; }
    auto city() const noexcept -> const std::string& { return m_city; }

private:
    const std::string m_street;
    const std::string m_apartment;
    const PostalCode m_postal_code;
    const std::string m_city;

    auto validate_street(std::string_view street) const noexcept -> bool;
    auto validate_apartment(std::string_view apartment) const noexcept -> bool;
    auto validate_city(std::string_view city) const noexcept -> bool;
};
