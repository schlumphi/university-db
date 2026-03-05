#pragma once
#include <string>

class Pesel {
public:
    Pesel(std::string_view number);

    auto value() const noexcept -> const std::string& { return m_number; }

private:
    const std::string m_number;
};
