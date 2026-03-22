#include <gtest/gtest.h>

#include "core/database.hpp"

class DatabaseTest : public ::testing::Test {
protected:
    Student abacki{
        "Adam",
        "Abacki",
        Address{"Warszawska 42", "2", PostalCode{"01-234"}, "Warszawa"},
        Pesel{"55030101193"},
        Gender::Male};

    Student babacki{
        "Bdam",
        "Babacki",
        Address{"Warszawska 43", "3", PostalCode{"01-234"}, "Warszawa"},
        Pesel{"55030101230"},
        Gender::Male};

    Student cabacki{
        "Cdam",
        "Cabacki",
        Address{"Warszawska 44", "4", PostalCode{"01-234"}, "Warszawa"},
        Pesel{"83050594899"},
        Gender::Male};

    Student dabacka{
        "Ddama",
        "Dabacka",
        Address{"Warszawska 45", "5", PostalCode{"01-234"}, "Warszawa"},
        Pesel{"03281592527"},
        Gender::Female};

    Student fabacki{
        "Fdam",
        "Fabacki",
        Address{"Warszawska 46", "6", PostalCode{"01-234"}, "Warszawa"},
        Pesel{"52030218632"},
        Gender::Male};

    Database db;

    void SetUp() override {
        db.add(abacki);
        db.add(babacki);
        db.add(cabacki);
        db.add(dabacka);
        db.add(fabacki);
    }
};

TEST_F(DatabaseTest, Display) {
    const std::string ref_db_display =
        "first_name|last_name|street|apartment|postal_code|city|index_num|pesel|gender\n"
        "Adam|Abacki|Warszawska 42|2|01-234|Warszawa|1|55030101193|male\n"
        "Bdam|Babacki|Warszawska 43|3|01-234|Warszawa|2|55030101230|male\n"
        "Cdam|Cabacki|Warszawska 44|4|01-234|Warszawa|3|83050594899|male\n"
        "Ddama|Dabacka|Warszawska 45|5|01-234|Warszawa|4|03281592527|female\n"
        "Fdam|Fabacki|Warszawska 46|6|01-234|Warszawa|5|52030218632|male\n";

    EXPECT_EQ(db.display(), ref_db_display);
}

TEST_F(DatabaseTest, AddDuplicateStudent) {
    EXPECT_THROW(db.add(abacki), std::invalid_argument);
}

TEST_F(DatabaseTest, SaveAndLoad) {
    const auto filepath{"./db.txt"};
    db.save(filepath);

    Database db_from_file;
    db_from_file.load(filepath);

    EXPECT_EQ(db.display(), db_from_file.display());
    EXPECT_EQ(db.students(), db_from_file.students());
}

TEST_F(DatabaseTest, DeleteByIndex) {
    const std::list<Student> expected{abacki, babacki, dabacka, fabacki};
    db.delete_by_index(3);
    EXPECT_EQ(db.students(), expected);
    EXPECT_THROW(db.delete_by_index(3), std::invalid_argument);
}

TEST_F(DatabaseTest, SortByName) {
    std::list<Student> expected{abacki, babacki, cabacki, dabacka, fabacki};
    db.sort_by_name(Database::SortOrder::Ascending);
    EXPECT_EQ(db.students(), expected);

    expected.reverse();
    db.sort_by_name(Database::SortOrder::Descending);
    EXPECT_EQ(db.students(), expected);
}

TEST_F(DatabaseTest, SortByPesel) {
    std::list<Student> expected{dabacka, cabacki, babacki, abacki, fabacki};
    db.sort_by_pesel(Database::SortOrder::Ascending);
    EXPECT_EQ(db.students(), expected);

    expected.reverse();
    db.sort_by_pesel(Database::SortOrder::Descending);
    EXPECT_EQ(db.students(), expected);
}

TEST_F(DatabaseTest, SearchByLastName) {
    const auto matches = db.search_by_last_name("Abacki");
    const std::list<Student> expected{abacki};

    EXPECT_EQ(matches, expected);
}

TEST_F(DatabaseTest, SearchByPesel) {
    const auto matches = db.search_by_pesel(Pesel{"55030101193"});
    const std::list<Student> expected{abacki};

    EXPECT_EQ(matches, expected);
}
