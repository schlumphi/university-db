#include "pesel.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

Pesel::Pesel(const std::string& number) : m_number(number) {
    if (number.length() != 11 || std::any_of(number.begin(), number.end(), [](char c) { return !std::isdigit(c); })) {
        throw std::runtime_error("Pesel::Pesel: expected 'number' to be 11 digits length.");
    }
}
