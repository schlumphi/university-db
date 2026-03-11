#pragma once
#include <optional>
#include <string>
#include <string_view>
#include "gender.hpp"

class Pesel {
public:
    enum class ErrorCode {
        InvalidPeselFormat
    };
    Pesel(const std::string& number);

    auto value() const noexcept -> const std::string& { return m_number; }
    auto gender() const noexcept -> const Gender;

private:
    static auto validate_format(const std::string& number) noexcept -> std::optional<ErrorCode>;
    static auto validate_correctness(const std::string& number) noexcept -> std::optional<ErrorCode>;

    const std::string m_number;
};

auto parse_pesel_error_code(Pesel::ErrorCode error) -> std::string_view;
