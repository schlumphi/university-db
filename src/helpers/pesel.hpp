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
    enum class ErrorCode {
        InvalidPeselFormat,
        InvalidPeselChecksum
    };

    Pesel(const std::string& number);

    const std::string& value() const noexcept { return m_number; }
    Gender gender() const noexcept;

    // TODO: validate day of the month
    static std::optional<ErrorCode> validate_format(const std::string& number) noexcept;
    static std::optional<ErrorCode> validate_correctness(const std::string& number) noexcept;

    static constexpr std::array<uint8_t, 11> weights{1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1};

    // checks if lhs is younger than rhs
    bool operator<(const Pesel& rhs) const noexcept;

    // checks if lhs is older than rhs
    bool operator>(const Pesel& rhs) const noexcept;

private:
    const std::string m_number;
};

std::string_view parse_pesel_error_code(Pesel::ErrorCode error);

Century derive_century(const Pesel& pesel);

uint64_t parse_day(const Pesel& pesel);

uint64_t parse_month(const Pesel& pesel, const Century century);

uint64_t parse_year(const Pesel& pesel, const Century century);

uint64_t approx_days_since_epoch(const Pesel& pesel);
