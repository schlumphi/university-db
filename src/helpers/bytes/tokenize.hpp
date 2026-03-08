#pragma once

#include <string>
#include <vector>

namespace bytes {
auto tokenize(const std::string& data, const char delim) -> std::vector<std::string>;
}  // namespace bytes
