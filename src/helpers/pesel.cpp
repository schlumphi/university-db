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

std::optional<Pesel::ErrorCode> Pesel::validate_format(const std::string& number) noexcept {
    if (number.length() != 11 || std::any_of(number.begin(), number.end(), [](char c) { return !std::isdigit(c); })) {
        return Pesel::ErrorCode::InvalidPeselFormat;
    }
    return std::nullopt;
}

std::optional<Pesel::ErrorCode> Pesel::validate_correctness(const std::string& number) noexcept {
    auto sum = std::inner_product(
        number.begin(), number.end(), weights.begin(),
        0ULL, std::plus<>(),
        [](char c, uint8_t w) { return (static_cast<uint8_t>(c) - 48) * w; });

    if (sum % 10 != 0) {
        return Pesel::ErrorCode::InvalidPeselChecksum;
    } else {
        return std::nullopt;
    }
}

Gender Pesel::gender() const noexcept {
    const auto tenth_digit = static_cast<uint8_t>((m_number.at(9)));
    if (tenth_digit % 2 == 0) {
        return Gender::Female;
    } else {
        return Gender::Male;
    }
}

// checks if lhs is younger than rhs
bool Pesel::operator<(const Pesel& rhs) const noexcept {
    const auto this_days = approx_days_since_epoch(*this);
    const auto rhs_days = approx_days_since_epoch(rhs);
    if (this_days < rhs_days) {
        return false;
    } else if (this_days == rhs_days) {
        return m_number.substr(6, 5) < rhs.value();
    } else {
        return true;
    }
}

// checks if lhs is older than rhs
bool Pesel::operator>(const Pesel& rhs) const noexcept {
    const auto this_days = approx_days_since_epoch(*this);
    const auto rhs_days = approx_days_since_epoch(rhs);
    if (this_days < rhs_days) {
        return true;
    } else if (this_days == rhs_days) {
        return m_number.substr(6, 5) < rhs.value();
    } else {
        return false;
    }
}

std::string_view parse_pesel_error_code(Pesel::ErrorCode error) {
    switch (error) {
    case Pesel::ErrorCode::InvalidPeselFormat:
        return "expected 'number' to be 11 digits length";
    case Pesel::ErrorCode::InvalidPeselChecksum:
        return "'number' is invalid due to incorrect checksum";
    default:
        return "Ok";
    }
}

Century derive_century(const Pesel& pesel) {
    const uint64_t month_code = std::stoi(pesel.value().substr(2, 1));

    switch (month_code) {
    case 8:
    case 9:
        return Century::Nineteenth;
    case 2:
    case 3:
        return Century::TwentyFirst;
    case 4:
    case 5:
        return Century::TwentySecond;
    case 6:
    case 7:
        return Century::TwentyThird;
    default:
        return Century::Twentieth;
    }
}

uint64_t parse_day(const Pesel& pesel) {
    return std::stoi(pesel.value().substr(4, 2));
}

uint64_t parse_month(const Pesel& pesel, const Century century) {
    const uint64_t month = std::stoi(pesel.value().substr(2, 2));
    switch (century) {
    case Century::Nineteenth:
        return month - 80ULL;
    case Century::TwentyFirst:
        return month - 20ULL;
    case Century::TwentySecond:
        return month - 40ULL;
    case Century::TwentyThird:
        return month - 60ULL;
    default:
        return month;
    }
}

uint64_t parse_year(const Pesel& pesel, const Century century) {
    const uint64_t year = std::stoi(pesel.value().substr(0, 2));
    switch (century) {
    case Century::Nineteenth:
        return year + 1800ULL;
    case Century::TwentyFirst:
        return year + 2000ULL;
    case Century::TwentySecond:
        return year + 2100ULL;
    case Century::TwentyThird:
        return year + 2200ULL;
    default:
        return year + 1900ULL;
    }
}

uint64_t approx_days_since_epoch(const Pesel& pesel) {
    const auto century = derive_century(pesel);
    const auto year = parse_year(pesel, century);
    const auto month = parse_month(pesel, century);
    const auto day = parse_day(pesel);

    return year * 365ULL + month * 30ULL + day;
}
