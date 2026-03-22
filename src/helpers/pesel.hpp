#pragma once
#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

#include "gender.hpp"

enum class Century {
    Nineteenth,
    Twentieth,
    TwentyFirst,
    TwentySecond,
    TwentyThird
};

class Pesel {
public:
    Pesel(const std::string& number);

    const std::string& value() const noexcept { return m_number; }
    Gender gender() const noexcept;

    static std::string validate_number(const std::string& number);

    static constexpr std::array<uint8_t, 11> weights{1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1};

    // checks if lhs is younger than rhs
    bool operator<(const Pesel& rhs) const noexcept;

    // checks if lhs is older than rhs
    bool operator>(const Pesel& rhs) const noexcept;

private:
    // TODO: validate day of the month
    static void validate_format(const std::string& number);
    static void validate_correctness(const std::string& number);

    const std::string m_number;
};

Century derive_century(const Pesel& pesel);

uint64_t parse_day(const Pesel& pesel);

uint64_t parse_month(const Pesel& pesel, const Century century);

uint64_t parse_year(const Pesel& pesel, const Century century);

uint64_t approx_days_since_epoch(const Pesel& pesel);
