#pragma once
#include <string>
#include "postal_code.hpp"

class Address {
public:
    Address(
        const std::string& street,
        const std::string& apartment,
        const PostalCode& postal_code,
        const std::string& city);

    auto street() const noexcept -> const std::string& { return m_street; }
    auto apartment() const noexcept -> const std::string& { return m_apartment; }
    auto postal_code() const noexcept -> const PostalCode& { return m_postal_code; }
    auto city() const noexcept -> const std::string& { return m_city; }

private:
    const std::string m_street;
    const std::string m_apartment;
    const PostalCode m_postal_code;
    const std::string m_city;

    auto validate_street(const std::string& street) const noexcept -> bool;
    auto validate_apartment(const std::string& apartment) const noexcept -> bool;
    auto validate_city(const std::string& city) const noexcept -> bool;
};
