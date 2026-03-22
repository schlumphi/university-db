#pragma once

#include <cctype>
#include <string>
#include <string_view>

namespace predicates {
bool contains_only_alpha(std::string_view data);

bool contains_only_digits(std::string_view data);

bool contains_only_alphanum(std::string_view data);

bool contains_only_lowercase_alpha(std::string_view data);

bool is_capitalized_alpha(std::string_view data);
}  // namespace predicates
