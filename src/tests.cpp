#include <gtest/gtest.h>

#include "core/database.hpp"
#include "core/student.hpp"

TEST(Student, ConstructorWithInvalidFirstNameThrowsError) {
    auto valid_last_name = "Abacki";
    auto valid_address = Address{
        "Warszawska 42",
        "2",
        PostalCode{"01-234"},
        "Warszawa"};
    auto valid_index = 0ULL;
    auto valid_pesel = Pesel{"55030101193"};
    auto valid_gender = Gender::Male;

    EXPECT_EQ(Student::validate_name(""), Student::ErrorCode::EmptyName);
    EXPECT_THROW(Student(
                     "",
                     valid_last_name,
                     valid_address,
                     valid_index,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("adam"), Student::ErrorCode::NameDoesntBeginWithUppercase);
    EXPECT_THROW(Student(
                     "adam",
                     valid_last_name,
                     valid_address,
                     valid_index,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("ADam"), Student::ErrorCode::NameContainsUppercaseCharacters);
    EXPECT_THROW(Student(
                     "ADam",
                     valid_last_name,
                     valid_address,
                     valid_index,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("Ada#m"), Student::ErrorCode::NameContainsInvalidCharacters);
    EXPECT_THROW(Student(
                     "Ada#m",
                     valid_last_name,
                     valid_address,
                     valid_index,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);
}

TEST(Student, ConstructorWithInvalidLastNameThrowsError) {
    auto valid_first_name = "Adam";
    auto valid_address = Address{
        "Warszawska 42",
        "2",
        PostalCode{"01-234"},
        "Warszawa"};
    auto valid_index = 0ULL;
    auto valid_pesel = Pesel{"55030101193"};
    auto valid_gender = Gender::Male;

    EXPECT_EQ(Student::validate_name(""), Student::ErrorCode::EmptyName);
    EXPECT_THROW(Student(
                     valid_first_name,
                     "",
                     valid_address,
                     valid_index,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("abacki"), Student::ErrorCode::NameDoesntBeginWithUppercase);
    EXPECT_THROW(Student(
                     valid_first_name,
                     "abacki",
                     valid_address,
                     valid_index,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("ABacki"), Student::ErrorCode::NameContainsUppercaseCharacters);
    EXPECT_THROW(Student(
                     valid_first_name,
                     "ABacki",
                     valid_address,
                     valid_index,
                     valid_pesel,
                     valid_gender),
                 std::invalid_argument);

    EXPECT_EQ(Student::validate_name("Abac#ki"), Student::ErrorCode::NameContainsInvalidCharacters);
    EXPECT_THROW(Student(
                     valid_first_name,
                     "Abac#ki",
                     valid_address,
                     valid_index,
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
        42ULL,
        Pesel{"55030101193"},
        Gender::Male};

    EXPECT_EQ(abacki.first_name(), "Adam");
    EXPECT_EQ(abacki.last_name(), "Abacki");
    EXPECT_EQ(abacki.address().street(), "Warszawska 42");
    EXPECT_EQ(abacki.address().apartment(), "2");
    EXPECT_EQ(abacki.address().postal_code().value(), "01-234");
    EXPECT_EQ(abacki.address().city(), "Warszawa");
    EXPECT_EQ(abacki.index_num(), 42ULL);
    EXPECT_EQ(abacki.pesel().value(), "55030101193");
    EXPECT_EQ(abacki.gender(), Gender::Male);
}

TEST(Database, AddingNewStudent) {
    const Student abacki{
        "Adam",
        "Abacki",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        42ULL,
        Pesel{"55030101193"},
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
    EXPECT_EQ(PostalCode::validate_code("0-000"), PostalCode::ErrorCode::InvalidCodeLen);
    EXPECT_THROW(PostalCode{"0-000"}, std::invalid_argument);

    EXPECT_EQ(PostalCode::validate_code("00000"), PostalCode::ErrorCode::InvalidCodeLen);
    EXPECT_THROW(PostalCode{"00000"}, std::invalid_argument);

    EXPECT_EQ(PostalCode::validate_code("000-000"), PostalCode::ErrorCode::InvalidCodeLen);
    EXPECT_THROW(PostalCode{"000-000"}, std::invalid_argument);

    EXPECT_EQ(PostalCode::validate_code("000000"), PostalCode::ErrorCode::InvalidCodeFormat);
    EXPECT_THROW(PostalCode{"000000"}, std::invalid_argument);

    EXPECT_EQ(PostalCode::validate_code("0-0000"), PostalCode::ErrorCode::InvalidCodeFormat);
    EXPECT_THROW(PostalCode{"0-0000"}, std::invalid_argument);

    EXPECT_EQ(PostalCode::validate_code("000-00"), PostalCode::ErrorCode::InvalidCodeFormat);
    EXPECT_THROW(PostalCode{"000-00"}, std::invalid_argument);

    EXPECT_EQ(PostalCode::validate_code("0000-0"), PostalCode::ErrorCode::InvalidCodeFormat);
    EXPECT_THROW(PostalCode{"0000-0"}, std::invalid_argument);
}

TEST(Address, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "Warsaw"));
}

TEST(Address, ConstructorWithInvalidStreetNameThrowsError) {
    const auto apartment = std::string{""};
    const auto postal_code = PostalCode{"01-234"};
    const auto city = std::string{"Warsaw"};

    EXPECT_EQ(Address::validate_street(""), Address::ErrorCode::StreetNameEmpty);
    EXPECT_THROW(
        Address("", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_street("Warszawska"), Address::ErrorCode::StreetNameInvalidFormat);
    EXPECT_THROW(
        Address("Warszawska", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_street("Wars#zawska 2"), Address::ErrorCode::StreetNameInvalidNameFormat);
    EXPECT_THROW(
        Address("Wars#zawska 2", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_street("Warszawska F"), Address::ErrorCode::StreetInvalidNumberFormat);
    EXPECT_THROW(
        Address("Warszawska F", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_street("Warszawska F2"), Address::ErrorCode::StreetInvalidNumberFormat);
    EXPECT_THROW(
        Address("Warszawska F2", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_street("Warszawska 2F2"), Address::ErrorCode::StreetInvalidNumberFormat);
    EXPECT_THROW(
        Address("Warszawska 2F2", apartment, postal_code, city),
        std::invalid_argument);
}

TEST(Address, ConstructorWithInvalidApartmentThrowsError) {
    const auto street = std::string{"Sezamkowa"};
    const auto postal_code = PostalCode{"01-234"};
    const auto city = std::string{"Warsaw"};

    EXPECT_EQ(Address::validate_apartment("/"), Address::ErrorCode::ApartmentInvalidCharacters);
    EXPECT_THROW(
        Address(street, "/", postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_apartment("2/"), Address::ErrorCode::ApartmentInvalidCharacters);
    EXPECT_THROW(
        Address(street, "2/", postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_apartment("/2"), Address::ErrorCode::ApartmentInvalidCharacters);
    EXPECT_THROW(
        Address(street, "/2", postal_code, city),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_apartment("2F#"), Address::ErrorCode::ApartmentInvalidCharacters);
    EXPECT_THROW(
        Address(street, "2F#", postal_code, city),
        std::invalid_argument);
}

TEST(Address, ConstructorWithInvalidCityNameThrowsError) {
    const auto street = std::string{"Sezamkowa"};
    const auto apartment = std::string{"42"};
    const auto postal_code = PostalCode{"01-234"};

    EXPECT_EQ(Address::validate_city(""), Address::ErrorCode::CityNameTooShort);
    EXPECT_THROW(
        Address(street, apartment, postal_code, ""),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_city("A"), Address::ErrorCode::CityNameTooShort);
    EXPECT_THROW(
        Address(street, apartment, postal_code, "A"),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_city("a"), Address::ErrorCode::CityNameTooShort);
    EXPECT_THROW(
        Address(street, apartment, postal_code, "a"),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_city("a42"), Address::ErrorCode::CityNameInvalidCharacters);
    EXPECT_THROW(
        Address(street, apartment, postal_code, "a42"),
        std::invalid_argument);

    EXPECT_EQ(Address::validate_city("oS"), Address::ErrorCode::CityNameDoesntStartWithCapitalLetter);
    EXPECT_THROW(
        Address(street, apartment, postal_code, "oS"),
        std::invalid_argument);
}

TEST(Pesel, ConstructorWithInvalidValidFormatThrowsError) {
    EXPECT_EQ(Pesel::validate_format("9876543210"), Pesel::ErrorCode::InvalidPeselFormat);
    EXPECT_THROW(Pesel("9876543210"), std::invalid_argument);

    EXPECT_EQ(Pesel::validate_format("9876543210c"), Pesel::ErrorCode::InvalidPeselFormat);
    EXPECT_THROW(Pesel("9876543210c"), std::invalid_argument);
}

TEST(Pesel, ConstructorWithInvalidChecksumThrowsError) {
    EXPECT_EQ(Pesel::validate_correctness("98765432100"), Pesel::ErrorCode::InvalidPeselChecksum);
    EXPECT_THROW(Pesel("98765432100"), std::invalid_argument);
}

TEST(Pesel, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(Pesel("55030101230"));
}
