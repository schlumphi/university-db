#include <gtest/gtest.h>

#include "core/database.hpp"
#include "core/student.hpp"

TEST(Student, ConstructorWithValidDataCreatesValidObject) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "ul. Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        42ULL,
        Pesel{"99123101234"},
        Gender::Male};

    EXPECT_EQ(abacki.first_name(), "Adam");
    EXPECT_EQ(abacki.last_name(), "Abacki");
    EXPECT_EQ(abacki.address().street(), "ul. Warszawska 42");
    EXPECT_EQ(abacki.address().apartment(), "2");
    EXPECT_EQ(abacki.address().postal_code().value(), "01-234");
    EXPECT_EQ(abacki.address().city(), "Warszawa");
    EXPECT_EQ(abacki.index_num(), 42ULL);
    EXPECT_EQ(abacki.pesel().value(), "99123101234");
    EXPECT_EQ(abacki.gender(), Gender::Male);
}

TEST(Database, AddingNewStudent) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "ul. Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        42ULL,
        Pesel{"99123101234"},
        Gender::Male};

    Database db;
    EXPECT_TRUE(db.add(abacki));
    EXPECT_FALSE(db.add(abacki));
}

TEST(PostalCode, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(PostalCode{"00-000"});
    EXPECT_NO_THROW(PostalCode{"01-000"});
    EXPECT_NO_THROW(PostalCode{"02-000"});
    EXPECT_NO_THROW(PostalCode{"99-999"});
}

TEST(PostalCode, ConstructorWithInvalidDataThrowsError) {
    EXPECT_THROW(PostalCode{"000000"}, std::invalid_argument);
    EXPECT_THROW(PostalCode{"000-000"}, std::invalid_argument);
    EXPECT_THROW(PostalCode{"0-0000"}, std::invalid_argument);
    EXPECT_THROW(PostalCode{"000-00"}, std::invalid_argument);
    EXPECT_THROW(PostalCode{"0000-0"}, std::invalid_argument);
    EXPECT_THROW(PostalCode{"0-000"}, std::invalid_argument);
    EXPECT_THROW(PostalCode{"00000"}, std::invalid_argument);
    EXPECT_THROW(PostalCode{"000000"}, std::invalid_argument);
}
