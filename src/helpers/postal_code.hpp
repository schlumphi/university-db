#pragma once
#include <string_view>

class PostalCode {
public:
    PostalCode(std::string_view code);

    auto value() const noexcept -> const std::string& { return m_code; }

private:
    const std::string m_code;
};
