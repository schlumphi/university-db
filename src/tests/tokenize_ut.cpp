#include <gtest/gtest.h>

#include "helpers/bytes/tokenize.hpp"

TEST(Tokenize, TokenizeWithoutDelimiter) {
    const std::string data{""};
    const char delimiter{' '};
    const std::vector<std::string_view> expected{""};

    auto tokens = bytes::tokenize(data, delimiter);

    EXPECT_EQ(tokens, expected);
}

TEST(Tokenize, TokenizeWithDelimiterInside) {
    const std::string data{"test test"};
    const char delimiter{' '};
    const std::vector<std::string_view> expected{"test", "test"};

    auto tokens = bytes::tokenize(data, delimiter);

    EXPECT_EQ(tokens, expected);
}

TEST(Tokenize, TokenizeWithDelimiterAtTheBegining) {
    const std::string data{" test"};
    const char delimiter{' '};
    const std::vector<std::string_view> expected{"", "test"};

    auto tokens = bytes::tokenize(data, delimiter);

    EXPECT_EQ(tokens, expected);
}

TEST(Tokenize, TokenizeWithDelimiterAtTheEnd) {
    const std::string data{"test "};
    const char delimiter{' '};
    const std::vector<std::string_view> expected{"test", ""};

    auto tokens = bytes::tokenize(data, delimiter);

    EXPECT_EQ(tokens, expected);
}

TEST(Tokenize, TokenizeWithDelimiterMixed) {
    const std::string data{" test test "};
    const char delimiter{' '};
    const std::vector<std::string_view> expected{"", "test", "test", ""};

    auto tokens = bytes::tokenize(data, delimiter);

    EXPECT_EQ(tokens, expected);
    EXPECT_TRUE(true);
}
