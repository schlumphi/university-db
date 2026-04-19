#pragma once
#include <string>

class PostalCode {
public:
    PostalCode(const std::string& code);

    const std::string& value() const noexcept { return m_code; }
    static std::string validate_code(const std::string& code);

private:
    const std::string m_code;
};
