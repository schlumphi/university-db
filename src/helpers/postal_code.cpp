#include "postal_code.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>

PostalCode::PostalCode(const std::string& code) : m_code(code) {
    if (code.length() != 6) {
        throw std::invalid_argument("PostalCode::PostalCode: expected 'code' to be 6 characters len.");
    }
    if (code[2] != '-') {
        throw std::invalid_argument("PostalCode::PostalCode: expected 'code' format: XX-XXX.");
    }
    auto digits = code.substr(0, 2) + code.substr(3, 3);
    if (std::any_of(digits.begin(), digits.end(), [](char c) { return !std::isdigit(c); })) {
        throw std::invalid_argument("PostalCode::PostalCode: expected 'code' format: XX-XXX.");
    }
}
