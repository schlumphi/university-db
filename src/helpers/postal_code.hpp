#pragma once
#include <string>

class PostalCode {
public:
    PostalCode(const std::string& code);

    auto value() const noexcept -> const std::string& { return m_code; }

private:
    const std::string m_code;
};
