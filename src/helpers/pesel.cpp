#include "pesel.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

Pesel::Pesel(const std::string& number) : m_number(number) {
    if (auto error = validate_format(number)) {
        throw std::invalid_argument(std::string(parse_pesel_error_code(*error)));
    }
}

auto Pesel::validate_format(const std::string& number) noexcept -> std::optional<Pesel::ErrorCode> {
    if (number.length() != 11 || std::any_of(number.begin(), number.end(), [](char c) { return !std::isdigit(c); })) {
        return Pesel::ErrorCode::InvalidPeselFormat;
    }
    return std::nullopt;
}

auto parse_pesel_error_code(Pesel::ErrorCode error) -> std::string_view {
    switch (error) {
    case Pesel::ErrorCode::InvalidPeselFormat:
        return "expected 'number' to be 11 digits length";
    default:
        return "Ok";
    }
}
