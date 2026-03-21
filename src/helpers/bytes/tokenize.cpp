#include "tokenize.hpp"

namespace bytes {
std::vector<std::string_view> tokenize(std::string_view data, const char delimiter) {
    std::vector<std::string_view> tokens;

    while (true) {
        auto pos = data.find(delimiter);

        if (pos == std::string_view::npos) {
            tokens.emplace_back(data);
            break;
        }

        tokens.emplace_back(data.substr(0, pos));
        data = data.substr(pos + 1);
    }

    return tokens;
}
}  // namespace bytes
