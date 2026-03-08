#include "pesel.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

Pesel::Pesel(const std::string& number) : m_number(number) {
    if (number.length() != 11 || std::any_of(number.begin(), number.end(), [](char c) { return !std::isdigit(c); })) {
        throw std::runtime_error("Pesel::Pesel: expected 'number' to be 11 digits length.");
    }
}

auto validate_number(const std::string& number) noexcept -> std::optional<Pesel::ErrorCode> {
    return std::nullopt;
}

auto parse_pesel_error_code(Pesel::ErrorCode error) -> std::string_view {
    switch (error) {
    case Pesel::ErrorCode::InvalidPeselLength:
        return "expected 'number' to be 11 digits length";
    default:
        return "Ok";
    }
}
