#include "postal_code.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>

#include "bytes/tokenize.hpp"

PostalCode::PostalCode(const std::string& code) : m_code(validate_code(code)) {}

std::string PostalCode::validate_code(const std::string& code) {
    auto tokens = bytes::tokenize(code, '-');
    if (tokens.size() != 2 || tokens.front().size() != 2 || tokens.back().size() != 3) {
        throw std::invalid_argument("expected 'code' format: XX-XXX, where X is digit character");
    }
    for (auto code_chunk : tokens) {
        if (std::any_of(code_chunk.begin(), code_chunk.end(), [](char c) { return !std::isdigit(c); })) {
            throw std::invalid_argument("expected 'code' format: XX-XXX, where X is digit character");
        }
    }
    return code;
}
