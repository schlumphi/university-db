#include <gtest/gtest.h>

#include "helpers/predicates/string_checks.hpp"

TEST(StringChecks, ContainsOnlyAlpha) {
    EXPECT_TRUE(predicates::contains_only_alpha("trAlaLala"));
    EXPECT_FALSE(predicates::contains_only_alpha("tr AlaLala"));
    EXPECT_FALSE(predicates::contains_only_alpha("tr2AlaLala"));
    EXPECT_FALSE(predicates::contains_only_alpha(""));
}

TEST(StringChecks, ContainsOnlyDigits) {
    EXPECT_TRUE(predicates::contains_only_digits("0700880"));
    EXPECT_FALSE(predicates::contains_only_digits("07a00880"));
    EXPECT_FALSE(predicates::contains_only_digits(""));
}

TEST(StringChecks, ContainsOnlyAlphanum) {
    EXPECT_TRUE(predicates::contains_only_alphanum("a070b088c0"));
    EXPECT_FALSE(predicates::contains_only_alphanum("a070b0 88c0"));
    EXPECT_FALSE(predicates::contains_only_alphanum("a070b0@88c0"));
    EXPECT_FALSE(predicates::contains_only_alphanum(""));
}

TEST(StringChecks, ContainsOnlyLowercaseAlpha) {
    EXPECT_TRUE(predicates::contains_only_lowercase_alpha("palisadajaktalala"));
    EXPECT_FALSE(predicates::contains_only_lowercase_alpha("palisadaJaktalala"));
    EXPECT_FALSE(predicates::contains_only_lowercase_alpha("palisada@jaktalala"));
    EXPECT_FALSE(predicates::contains_only_lowercase_alpha("palisada jaktalala"));
    EXPECT_FALSE(predicates::contains_only_lowercase_alpha(""));
}

TEST(StringChecks, IsCapitalizedAlpha) {
    EXPECT_TRUE(predicates::is_capitalized_alpha("Niechsiemurypnadogory"));
    EXPECT_FALSE(predicates::is_capitalized_alpha("niechsiemurypnadogory"));
    EXPECT_FALSE(predicates::is_capitalized_alpha("Niechsiemu rypnadogory"));
    EXPECT_FALSE(predicates::is_capitalized_alpha(""));
}
