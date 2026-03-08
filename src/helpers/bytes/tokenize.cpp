#include "tokenize.hpp"

auto tokenize(const std::string& data, const char delim) -> std::vector<std::string> {
    std::vector<std::string> tokens;
    std::string buffer;
    for (auto c : data) {
        if (c == delim && !buffer.empty()) {
            tokens.push_back(buffer);
            buffer.clear();
        } else if (c != delim) {
            buffer.push_back(c);
        }
    }
    if (!buffer.empty()) {
        tokens.push_back(buffer);
    }

    return tokens;
}
