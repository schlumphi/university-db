#include "string_checks.hpp"

#include <algorithm>

namespace predicates {
bool contains_only_alpha(std::string_view data) {
    if (data.empty()) {
        return false;
    }
    if (std::any_of(data.begin(), data.end(), [](char c) { return !std::isalpha(c); })) {
        return false;
    }
    return true;
}

bool contains_only_digits(std::string_view data) {
    if (data.empty()) {
        return false;
    }
    if (std::any_of(data.begin(), data.end(), [](char c) { return !std::isdigit(c); })) {
        return false;
    }
    return true;
}

bool contains_only_alphanum(std::string_view data) {
    if (data.empty()) {
        return false;
    }
    if (std::any_of(data.begin(), data.end(), [](char c) { return !std::isalnum(c); })) {
        return false;
    }
    return true;
}

bool contains_only_lowercase_alpha(std::string_view data) {
    if (data.empty()) {
        return false;
    }
    if (std::any_of(data.begin(), data.end(), [](char c) { return !std::isalpha(c) || !std::islower(c); })) {
        return false;
    }
    return true;
}

bool is_capitalized_alpha(std::string_view data) {
    if (data.empty()) {
        return false;
    }
    if (!std::isupper(data.front())) {
        return false;
    }
    if (!contains_only_lowercase_alpha(data.substr(1))) {
        return false;
    }

    return true;
}
}  // namespace predicates
