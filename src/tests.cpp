#include <gtest/gtest.h>
#include "core/database.hpp"
#include "core/student.hpp"

TEST(Database, SortByPesel) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    Student babacki{
        "Bdam",
        "Babacki",
        Address{
            "Warszawska 43",
            "3",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101230"},
        Gender::Male};

    Student cabacki{
        "Cdam",
        "Cabacki",
        Address{
            "Warszawska 44",
            "4",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"83050594899"},
        Gender::Male};

    Student dabacka{
        "Ddama",
        "Dabacka",
        Address{
            "Warszawska 45",
            "5",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"03281592527"},
        Gender::Female};

    Student fabacki{
        "Fdam",
        "Fabacki",
        Address{
            "Warszawska 46",
            "6",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"52030218632"},
        Gender::Male};

    Database db;
    db.add(abacki);
    db.add(babacki);
    db.add(cabacki);
    db.add(dabacka);
    db.add(fabacki);

    const std::string ref_db_display_sorted_ascending =
        "first_name|last_name|street|apartment|postal_code|city|index_num|pesel|gender\n"
        "Ddama|Dabacka|Warszawska 45|5|01-234|Warszawa|4|03281592527|female\n"
        "Cdam|Cabacki|Warszawska 44|4|01-234|Warszawa|3|83050594899|male\n"
        "Bdam|Babacki|Warszawska 43|3|01-234|Warszawa|2|55030101230|male\n"
        "Adam|Abacki|Warszawska 42|2|01-234|Warszawa|1|55030101193|male\n"
        "Fdam|Fabacki|Warszawska 46|6|01-234|Warszawa|5|52030218632|male\n";

    db.sort_by_pesel(Database::SortOrder::Ascending);
    EXPECT_EQ(db.display(), ref_db_display_sorted_ascending);

    const std::string ref_db_display_sorted_descending =
        "first_name|last_name|street|apartment|postal_code|city|index_num|pesel|gender\n"
        "Fdam|Fabacki|Warszawska 46|6|01-234|Warszawa|5|52030218632|male\n"
        "Bdam|Babacki|Warszawska 43|3|01-234|Warszawa|2|55030101230|male\n"
        "Adam|Abacki|Warszawska 42|2|01-234|Warszawa|1|55030101193|male\n"
        "Cdam|Cabacki|Warszawska 44|4|01-234|Warszawa|3|83050594899|male\n"
        "Ddama|Dabacka|Warszawska 45|5|01-234|Warszawa|4|03281592527|female\n";

    db.sort_by_pesel(Database::SortOrder::Descending);
    EXPECT_EQ(db.display(), ref_db_display_sorted_descending);
}

TEST(Database, SearchByLastName) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    Student babacki{
        "Bdam",
        "Babacki",
        Address{
            "Warszawska 43",
            "3",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101230"},
        Gender::Male};

    Database db;
    db.add(abacki);
    db.add(babacki);

    const auto matches = db.search_by_last_name("Abacki");
    const std::list<Student> ref_matches = {abacki};

    EXPECT_EQ(matches, ref_matches);
}

TEST(Database, SearchByPesel) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    Student babacki{
        "Bdam",
        "Babacki",
        Address{
            "Warszawska 43",
            "3",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101230"},
        Gender::Male};

    Database db;
    db.add(abacki);
    db.add(babacki);

    const auto matches = db.search_by_pesel(Pesel{"55030101193"});
    const std::list<Student> ref_matches = {abacki};

    EXPECT_EQ(matches, ref_matches);
}

TEST(Database, DisplayDatabase) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    Database db;
    db.add(abacki);

    const std::string ref_db_display =
        "first_name|last_name|street|apartment|postal_code|city|index_num|pesel|gender\n"
        "Adam|Abacki|Warszawska 42|2|01-234|Warszawa|1|55030101193|male\n";

    EXPECT_EQ(db.display(), ref_db_display);
}

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
}

TEST(Database, AddingNewStudent) {
    Student abacki{
        "Adam",
        "Abacki",
        Address{
            "Warszawska 42",
            "2",
            PostalCode{"01-234"},
            "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    Database db;
    EXPECT_EQ(abacki.index_num(), 0ULL);
    EXPECT_EQ(db.add(abacki), std::nullopt);
    EXPECT_EQ(abacki.index_num(), 1ULL);
    EXPECT_EQ(db.add(abacki), Database::ErrorCode::StudentAlreadyExistsInDb);
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
