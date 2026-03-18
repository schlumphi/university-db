#include "postal_code.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>

PostalCode::PostalCode(const std::string& code) : m_code(code) {
    if (auto error = validate_code(code)) {
        throw std::invalid_argument(std::string(parse_postal_code_error_code(*error)));
    }
}

auto PostalCode::validate_code(const std::string& code) noexcept -> std::optional<ErrorCode> {
    if (code.length() != 6) {
        return ErrorCode::InvalidCodeLen;
    }
    if (code[2] != '-') {
        return ErrorCode::InvalidCodeFormat;
    }

    auto digits = code.substr(0, 2) + code.substr(3, 3);
    if (std::any_of(digits.begin(), digits.end(), [](char c) { return !std::isdigit(c); })) {
        return ErrorCode::InvalidCodeFormat;
    }
    return std::nullopt;
}

auto parse_postal_code_error_code(PostalCode::ErrorCode error) -> std::string_view {
    switch (error) {
    case PostalCode::ErrorCode::InvalidCodeLen:
        return "expected 'code' to be 6 characters len";
    case PostalCode::ErrorCode::InvalidCodeFormat:
        return "expected 'code' format: XX-XXX";
    default:
        return "Ok";
    }
}
