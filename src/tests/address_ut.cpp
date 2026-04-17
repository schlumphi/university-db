#include <gtest/gtest.h>

#include "helpers/address.hpp"
#include "helpers/postal_code.hpp"

class AddressTest : public ::testing::Test {
protected:
    const std::string valid_street{"Sezamkowa 42"};
    const std::string valid_apartment{"2"};
    const PostalCode valid_postal_code{"01-234"};
    const std::string valid_city{"Warsaw"};
};

TEST(Address, ConstructorWithValidDataCreatesValidObject) {
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "Warsaw"));
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "New York"));
    EXPECT_NO_THROW(Address("Sezamkowa 42", "2", PostalCode{"01-234"}, "Bielsko-Biala"));

    EXPECT_NO_THROW(Address("3 Maja 42", "2", PostalCode{"01-234"}, "Warsaw"));
    EXPECT_NO_THROW(Address("11 Listopada 42", "2", PostalCode{"01-234"}, "Warsaw"));
    EXPECT_NO_THROW(Address("Edwarda Rydza-Smiglego 42", "2", PostalCode{"01-234"}, "Warsaw"));
    EXPECT_NO_THROW(Address("Dywizjonu 303 42", "2", PostalCode{"01-234"}, "Warsaw"));
}

TEST_F(AddressTest, ConstructorWithInvalidStreetNameThrowsError) {
    EXPECT_THROW(
        Address("", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Wars#zawska 2", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska F", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("WarsZawska 2", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska F2", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("Warszawska 2F2", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("11 Listopada", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("!@#$ 2", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address("!@#$", valid_apartment, valid_postal_code, valid_city),
        std::invalid_argument);
}

TEST_F(AddressTest, ConstructorWithInvalidApartmentThrowsError) {
    EXPECT_THROW(
        Address(valid_street, "/", valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, "2/", valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, "/2", valid_postal_code, valid_city),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, "2F#", valid_postal_code, valid_city),
        std::invalid_argument);
}

TEST_F(AddressTest, ConstructorWithInvalidCityNameThrowsError) {
    EXPECT_THROW(
        Address(valid_street, valid_apartment, valid_postal_code, ""),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, valid_apartment, valid_postal_code, "A"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, valid_apartment, valid_postal_code, "a"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, valid_apartment, valid_postal_code, "a42"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, valid_apartment, valid_postal_code, "A42"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, valid_apartment, valid_postal_code, "oS"),
        std::invalid_argument);

    EXPECT_THROW(
        Address(valid_street, valid_apartment, valid_postal_code, "OS"),
        std::invalid_argument);
}

TEST(Address, ConstructingNullAddress) {
    auto null_address = Address::null();
    EXPECT_EQ(null_address.street(), "Null 1");
    EXPECT_EQ(null_address.apartment(), "");
    EXPECT_EQ(null_address.postal_code().value(), PostalCode::null().value());
    EXPECT_EQ(null_address.city(), "Null");
}
