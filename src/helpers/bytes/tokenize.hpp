#pragma once

#include <string_view>
#include <vector>

namespace bytes {
std::vector<std::string_view> tokenize(std::string_view data, const char delimiter);
}  // namespace bytes
