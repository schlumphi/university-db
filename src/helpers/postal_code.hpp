#pragma once
#include <optional>
#include <string>

class PostalCode {
public:
    enum class ErrorCode {
        InvalidCodeLen,
        InvalidCodeFormat
    };
    PostalCode(const std::string& code);

    const std::string& value() const noexcept { return m_code; }
    static std::optional<ErrorCode> validate_code(const std::string& code) noexcept;

private:
    const std::string m_code;
};

std::string_view parse_postal_code_error_code(PostalCode::ErrorCode error);
