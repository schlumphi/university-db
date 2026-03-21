#include <gtest/gtest.h>

#include "helpers/address.hpp"
#include "helpers/postal_code.hpp"

TEST(Address, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "Warsaw"));
    // EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "New York"));
    // EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "Bielsko-Biala"));
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

    // EXPECT_EQ(Address::validate_street("!@#$ 2"), Address::ErrorCode::StreetNameInvalidNameFormat);
    // EXPECT_THROW(
    //     Address("!@#$ 2", apartment, postal_code, city),
    //     std::invalid_argument);

    // EXPECT_EQ(Address::validate_street("!@#$"), Address::ErrorCode::StreetNameInvalidFormat);
    // EXPECT_THROW(
    //     Address("!@#$", apartment, postal_code, city),
    //     std::invalid_argument);
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
