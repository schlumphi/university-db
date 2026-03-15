#pragma once
#include <array>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include "gender.hpp"

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
    auto operator<(const Pesel& rhs) const noexcept -> bool {
        return false;
    }

private:
    const std::string m_number;
};

auto parse_pesel_error_code(Pesel::ErrorCode error) -> std::string_view;
