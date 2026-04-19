#include <gtest/gtest.h>

#include "helpers/pesel.hpp"

TEST(Pesel, ConstructorWithInvalidValidFormatThrowsError) {
    EXPECT_THROW(Pesel("9876543210"), std::invalid_argument);

    EXPECT_THROW(Pesel("9876543210c"), std::invalid_argument);
}

TEST(Pesel, ConstructorWithInvalidChecksumThrowsError) {
    EXPECT_THROW(Pesel("98765432100"), std::invalid_argument);
}

TEST(Pesel, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(Pesel("55030101230"));
}
