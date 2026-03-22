#include <gtest/gtest.h>

#include "core/student.hpp"

class StudentTest : public ::testing::Test {
protected:
    const std::string valid_first_name{"Adam"};
    const std::string valid_last_name{"Abacki"};
    const Address valid_address{
        "Sezamkowa 42",
        "2",
        PostalCode{"01-234"},
        "Warsaw"};
    const Pesel valid_pesel{"55030101193"};
    const Gender valid_gender{Gender::Male};
};

TEST_F(StudentTest, ConstructorWithInvalidFirstNameThrowsError) {
    EXPECT_THROW(Student(
                     "",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_THROW(Student(
                     "A",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_THROW(Student(
                     "adam",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_THROW(Student(
                     "ADam",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_THROW(Student(
                     "Ada#m",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);
}

TEST_F(StudentTest, ConstructorWithInvalidLastNameThrowsError) {
    EXPECT_THROW(Student(
                     valid_first_name,
                     "",
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_THROW(Student(
                     valid_first_name,
                     "abacki",
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_THROW(Student(
                     valid_first_name,
                     "ABacki",
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_THROW(Student(
                     valid_first_name,
                     "Abac#ki",
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);
}

TEST(Student, ConstructorWithValidDataCreatesValidObject) {
    const Student abacki{
        "Adam",
        "Abacki",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    EXPECT_EQ(abacki.first_name(), "Adam");
    EXPECT_EQ(abacki.last_name(), "Abacki");
    EXPECT_EQ(abacki.address().street(), "Warszawska 42");
    EXPECT_EQ(abacki.address().apartment(), "2");
    EXPECT_EQ(abacki.address().postal_code().value(), "01-234");
    EXPECT_EQ(abacki.address().city(), "Warszawa");
    EXPECT_EQ(abacki.index_num(), 0ULL);
    EXPECT_EQ(abacki.pesel().value(), "55030101193");
    EXPECT_EQ(abacki.gender(), Gender::Male);

    const Student przerwa{
        "Adam",
        "Przerwa-Tetmajer",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    EXPECT_EQ(przerwa.first_name(), "Adam");
    EXPECT_EQ(przerwa.last_name(), "Przerwa-Tetmajer");
    EXPECT_EQ(przerwa.address().street(), "Warszawska 42");
    EXPECT_EQ(przerwa.address().apartment(), "2");
    EXPECT_EQ(przerwa.address().postal_code().value(), "01-234");
    EXPECT_EQ(przerwa.address().city(), "Warszawa");
    EXPECT_EQ(przerwa.index_num(), 0ULL);
    EXPECT_EQ(przerwa.pesel().value(), "55030101193");
    EXPECT_EQ(przerwa.gender(), Gender::Male);
}
