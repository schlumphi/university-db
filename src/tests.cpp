#include <gtest/gtest.h>

#include "core/database.hpp"
#include "core/student.hpp"

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
        Pesel{"99123101234"},
        Gender::Male};

    EXPECT_EQ(abacki.first_name(), "Adam");
    EXPECT_EQ(abacki.last_name(), "Abacki");
    EXPECT_EQ(abacki.address().street(), "Warszawska 42");
    EXPECT_EQ(abacki.address().apartment(), "2");
    EXPECT_EQ(abacki.address().postal_code().value(), "01-234");
    EXPECT_EQ(abacki.address().city(), "Warszawa");
    EXPECT_EQ(abacki.index_num(), 42ULL);
    EXPECT_EQ(abacki.pesel().value(), "99123101234");
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
