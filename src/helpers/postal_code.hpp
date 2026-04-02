#pragma once
#include <string>

class PostalCode {
public:
    PostalCode(const std::string& code);

    const std::string& value() const noexcept { return m_code; }
    static std::string validate_code(const std::string& code);

    static PostalCode null() noexcept { return PostalCode("00-000"); }

private:
    const std::string m_code;
};
