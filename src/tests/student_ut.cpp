#include <gtest/gtest.h>

#include "core/student.hpp"

TEST(Student, ConstructorWithInvalidFirstNameThrowsError) {
    const auto valid_last_name = "Abacki";
    const auto valid_address = Address{
        "Warszawska 42",
        "2",
        PostalCode{"01-234"},
        "Warszawa"};
    const auto valid_pesel = Pesel{"55030101193"};
    const auto valid_gender = Gender::Male;

    EXPECT_EQ(Student::validate_name(""), Student::ErrorCode::EmptyName);
    EXPECT_THROW(Student(
                     "",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("adam"), Student::ErrorCode::NameDoesntBeginWithUppercase);
    EXPECT_THROW(Student(
                     "adam",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("ADam"), Student::ErrorCode::NameContainsUppercaseCharacters);
    EXPECT_THROW(Student(
                     "ADam",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("Ada#m"), Student::ErrorCode::NameContainsInvalidCharacters);
    EXPECT_THROW(Student(
                     "Ada#m",
                     valid_last_name,
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);
}

TEST(Student, ConstructorWithInvalidLastNameThrowsError) {
    const auto valid_first_name = "Adam";
    const auto valid_address = Address{
        "Warszawska 42",
        "2",
        PostalCode{"01-234"},
        "Warszawa"};
    const auto valid_pesel = Pesel{"55030101193"};
    const auto valid_gender = Gender::Male;

    EXPECT_EQ(Student::validate_name(""), Student::ErrorCode::EmptyName);
    EXPECT_THROW(Student(
                     valid_first_name,
                     "",
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("abacki"), Student::ErrorCode::NameDoesntBeginWithUppercase);
    EXPECT_THROW(Student(
                     valid_first_name,
                     "abacki",
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("ABacki"), Student::ErrorCode::NameContainsUppercaseCharacters);
    EXPECT_THROW(Student(
                     valid_first_name,
                     "ABacki",
                     valid_address,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("Abac#ki"), Student::ErrorCode::NameContainsInvalidCharacters);
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

    // const Student przerwa{
    //     "Adam",
    //     "Przerwa-Tetmajer",
    //     Address{
    //         "Warszawska 42",
    //         "2",
    //         PostalCode{"01-234"},
    //         "Warszawa"},
    //     Pesel{"55030101193"},
    //     Gender::Male};

    // EXPECT_EQ(abacki.first_name(), "Adam");
    // EXPECT_EQ(abacki.last_name(), "Przerwa-Tetmajer");
    // EXPECT_EQ(abacki.address().street(), "Warszawska 42");
    // EXPECT_EQ(abacki.address().apartment(), "2");
    // EXPECT_EQ(abacki.address().postal_code().value(), "01-234");
    // EXPECT_EQ(abacki.address().city(), "Warszawa");
    // EXPECT_EQ(abacki.index_num(), 0ULL);
    // EXPECT_EQ(abacki.pesel().value(), "55030101193");
    // EXPECT_EQ(abacki.gender(), Gender::Male);
}
