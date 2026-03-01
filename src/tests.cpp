#include <gtest/gtest.h>

#include "core/database.hpp"
#include "core/student.hpp"

TEST(Student, ConstructorWithValidDataCreatesValidObject) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "ul. Warszawska",
            "42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        42ULL,
        Pesel{"99123101234"},
        Gender::Male};

    EXPECT_STREQ(abacki.first_name(), "Adam");
    EXPECT_STREQ(abacki.last_name(), "Abacki");
    EXPECT_STREQ(abacki.address().street(), "ul. Warszawska");
    EXPECT_STREQ(abacki.address().house_number(), "42");
    EXPECT_STREQ(abacki.address().apartment_number(), "2");
    EXPECT_STREQ(abacki.postal_code().value(), "01-234");
    EXPECT_STREQ(abacki.city(), "Warszawa");
    EXPECT_EQ(abacki.index_num(), 42ULL);
    EXPECT_STREQ(abacki.pesel().value(), "99123101234");
    EXPECT_EQ(abacki.gender(), Gender::Male);
}

TEST(Database, NewStudentAdding) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "ul. Warszawska",
            "42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        42ULL,
        Pesel{"99123101234"},
        Gender::Male};

    Database db;
    EXPECT_TRUE(db.add(abacki));
}
