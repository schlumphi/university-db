#include <gtest/gtest.h>

#include "helpers/postal_code.hpp"

TEST(PostalCode, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(PostalCode{"00-000"});
    EXPECT_NO_THROW(PostalCode{"01-000"});
    EXPECT_NO_THROW(PostalCode{"02-000"});
    EXPECT_NO_THROW(PostalCode{"99-999"});
}

TEST(PostalCode, ConstructorWithInvalidDataThrowsError) {
    EXPECT_THROW(PostalCode{"0-000"}, std::invalid_argument);

    EXPECT_THROW(PostalCode{"00000"}, std::invalid_argument);

    EXPECT_THROW(PostalCode{"000-000"}, std::invalid_argument);

    EXPECT_THROW(PostalCode{"000000"}, std::invalid_argument);

    EXPECT_THROW(PostalCode{"0-0000"}, std::invalid_argument);

    EXPECT_THROW(PostalCode{"000-00"}, std::invalid_argument);

    EXPECT_THROW(PostalCode{"0000-0"}, std::invalid_argument);
}
