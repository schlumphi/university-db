#include <gtest/gtest.h>

#include "helpers/address.hpp"
#include "helpers/postal_code.hpp"

TEST(Address, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "Warsaw"));
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "New York"));
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "Bielsko-Biala"));
}

TEST(Address, ConstructorWithInvalidStreetNameThrowsError) {
    const auto apartment = std::string{""};
    const auto postal_code = PostalCode{"01-234"};
    const auto city = std::string{"Warsaw"};

    EXPECT_THROW(
        Address("", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Wars#zawska 2", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska F", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska F2", apartment, postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska 2F2", apartment, postal_code, city),
        std::invalid_argument);

    // EXPECT_THROW(
    //     Address("!@#$ 2", apartment, postal_code, city),
    //     std::invalid_argument);

    // EXPECT_THROW(
    //     Address("!@#$", apartment, postal_code, city),
    //     std::invalid_argument);
}

TEST(Address, ConstructorWithInvalidApartmentThrowsError) {
    const auto street = std::string{"Sezamkowa"};
    const auto postal_code = PostalCode{"01-234"};
    const auto city = std::string{"Warsaw"};

    EXPECT_THROW(
        Address(street, "/", postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, "2/", postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, "/2", postal_code, city),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, "2F#", postal_code, city),
        std::invalid_argument);
}

TEST(Address, ConstructorWithInvalidCityNameThrowsError) {
    const auto street = std::string{"Sezamkowa"};
    const auto apartment = std::string{"42"};
    const auto postal_code = PostalCode{"01-234"};

    EXPECT_THROW(
        Address(street, apartment, postal_code, ""),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, apartment, postal_code, "A"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, apartment, postal_code, "a"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, apartment, postal_code, "a42"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, apartment, postal_code, "A42"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, apartment, postal_code, "oS"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(street, apartment, postal_code, "OS"),
        std::invalid_argument);
}
