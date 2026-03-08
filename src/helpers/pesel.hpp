#pragma once
#include <optional>
#include <string>
#include <string_view>

class Pesel {
public:
    enum class ErrorCode {
        InvalidPeselLength
    };
    Pesel(const std::string& number);

    auto value() const noexcept -> const std::string& { return m_number; }

private:
    static auto validate_number(const std::string& number) noexcept -> std::optional<ErrorCode>;
    const std::string m_number;
};

auto parse_pesel_error_code(Pesel::ErrorCode error) -> std::string_view;
