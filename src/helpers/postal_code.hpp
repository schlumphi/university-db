#pragma once
#include <string>

class PostalCode {
public:
    enum class ErrorCode {
        Ok,
        InvalidCodeLen,
        InvalidCodeFormat
    };
    PostalCode(const std::string& code);

    auto value() const noexcept -> const std::string& { return m_code; }

private:
    static auto validate_code(const std::string& code) noexcept -> ErrorCode;

    const std::string m_code;
};

auto parse_postal_code_error_code(PostalCode::ErrorCode error) -> std::string_view;
