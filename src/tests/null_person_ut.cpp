#include <gtest/gtest.h>

#include "core/null_person.hpp"

TEST(NullPerson, ConstructingNullPerson) {
    EXPECT_NO_THROW(NullPerson());
}
