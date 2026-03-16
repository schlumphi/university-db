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

    auto value() const noexcept -> const std::string& { return m_number; }
    auto gender() const noexcept -> const Gender;

    static auto validate_format(const std::string& number) noexcept -> std::optional<ErrorCode>;
    static auto validate_correctness(const std::string& number) noexcept -> std::optional<ErrorCode>;

    static constexpr std::array<uint8_t, 11> weights{1, 3, 7, 9, 1, 3, 7, 9, 1, 3, 1};

    // checks if lhs is younger than rhs
    auto operator<(const Pesel& rhs) const noexcept -> bool;

private:
    const std::string m_number;
};

auto parse_pesel_error_code(Pesel::ErrorCode error) -> std::string_view;

auto derive_century(const Pesel& pesel) -> Century;

auto parse_day(const Pesel& pesel) -> uint64_t;

auto parse_month(const Pesel& pesel, const Century century) -> uint64_t;

auto parse_year(const Pesel& pesel, const Century century) -> uint64_t;

auto approx_days_since_epoch(const Pesel& pesel) -> uint64_t;
