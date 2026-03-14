#include "pesel.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>

Pesel::Pesel(const std::string& number) : m_number(number) {
    if (auto error = validate_format(number)) {
        throw std::invalid_argument(std::string(parse_pesel_error_code(*error)));
    }

    if (auto error = validate_correctness(number)) {
        throw std::invalid_argument(std::string(parse_pesel_error_code(*error)));
    }
}

auto Pesel::validate_format(const std::string& number) noexcept -> std::optional<Pesel::ErrorCode> {
    if (number.length() != 11 || std::any_of(number.begin(), number.end(), [](char c) { return !std::isdigit(c); })) {
        return Pesel::ErrorCode::InvalidPeselFormat;
    }
    return std::nullopt;
}

auto Pesel::validate_correctness(const std::string& number) noexcept -> std::optional<ErrorCode> {
    auto sum = std::inner_product(
        number.begin(), number.end(), weights.begin(),
        0ULL, std::plus<>(),
        [](char c, uint8_t w) { return (static_cast<uint8_t>(c) - 48) * w; });

    std::cout << sum << "\n";

    if (sum % 10 != 0) {
        return Pesel::ErrorCode::InvalidPeselChecksum;
    }
    return std::nullopt;
}

auto Pesel::gender() const noexcept -> const Gender {
    auto tenth_digit = static_cast<uint8_t>((m_number.at(9)));
    if (tenth_digit % 2 == 0) {
        return Gender::Female;
    } else {
        return Gender::Male;
    }
}

auto parse_pesel_error_code(Pesel::ErrorCode error) -> std::string_view {
    switch (error) {
    case Pesel::ErrorCode::InvalidPeselFormat:
        return "expected 'number' to be 11 digits length";
    case Pesel::ErrorCode::InvalidPeselChecksum:
        return "'number' is invalid due to incorrect checksum";
    default:
        return "Ok";
    }
}
