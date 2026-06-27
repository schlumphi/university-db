#include <gtest/gtest.h>

#include "core/database.hpp"

class DatabaseTest : public ::testing::Test {
protected:
    std::unique_ptr<Student> abacki_ptr = std::make_unique<Student>("Adam",
                                                                    "Abacki",
                                                                    Address{"Warszawska 42", "2", PostalCode{"01-234"}, "Warszawa"},
                                                                    Pesel{"55030101193"},
                                                                    Gender::Male);
    Student* abacki = abacki_ptr.get();
    std::unique_ptr<Student> babacki_ptr = std::make_unique<Student>("Bdam",
                                                                     "Babacki",
                                                                     Address{"Warszawska 43", "3", PostalCode{"01-234"}, "Warszawa"},
                                                                     Pesel{"55030101230"},
                                                                     Gender::Male);

    Student* babacki = babacki_ptr.get();
    std::unique_ptr<Student> cabacki_ptr = std::make_unique<Student>("Cdam",
                                                                     "Cabacki",
                                                                     Address{"Warszawska 44", "4", PostalCode{"01-234"}, "Warszawa"},
                                                                     Pesel{"83050594899"},
                                                                     Gender::Male);

    Student* cabacki = cabacki_ptr.get();
    std::unique_ptr<Student> dabacka_ptr = std::make_unique<Student>("Ddama",
                                                                     "Dabacka",
                                                                     Address{"Warszawska 45", "5", PostalCode{"01-234"}, "Warszawa"},
                                                                     Pesel{"03281592527"},
                                                                     Gender::Female);

    Student* dabacka = dabacka_ptr.get();
    std::unique_ptr<Student> fabacki_ptr = std::make_unique<Student>("Fdam",
                                                                     "Fabacki",
                                                                     Address{"Warszawska 46", "6", PostalCode{"01-234"}, "Warszawa"},
                                                                     Pesel{"52030218632"},
                                                                     Gender::Male);

    Student* fabacki = fabacki_ptr.get();

    std::unique_ptr<Employee> gabacki_ptr = std::make_unique<Employee>("Gdam",
                                                                       "Gabacki",
                                                                       Address{"Warszawska 47", "7", PostalCode{"01-234"}, "Warszawa"},
                                                                       Pesel{"71030467716"},
                                                                       Gender::Male);

    Employee* gabacki = gabacki_ptr.get();

    Database db;

    void SetUp() override {
        db.add(std::move(abacki_ptr));
        db.add(std::move(babacki_ptr));
        db.add(std::move(cabacki_ptr));
        db.add(std::move(dabacka_ptr));
        db.add(std::move(fabacki_ptr));
        db.add(std::move(gabacki_ptr));
    }
};

TEST_F(DatabaseTest, Display) {
    const std::string ref_db_display =
        "first_name|last_name|street|apartment|postal_code|city|pesel|gender|index_num|salary\n"

        "Adam|Abacki|Warszawska 42|2|01-234|Warszawa|55030101193|male|" +
        std::to_string(abacki->index_num()) +
        "|\n"

        "Bdam|Babacki|Warszawska 43|3|01-234|Warszawa|55030101230|male|" +
        std::to_string(babacki->index_num()) +
        "|\n"

        "Cdam|Cabacki|Warszawska 44|4|01-234|Warszawa|83050594899|male|" +
        std::to_string(cabacki->index_num()) +
        "|\n"

        "Ddama|Dabacka|Warszawska 45|5|01-234|Warszawa|03281592527|female|" +
        std::to_string(dabacka->index_num()) +
        "|\n"

        "Fdam|Fabacki|Warszawska 46|6|01-234|Warszawa|52030218632|male|" +
        std::to_string(fabacki->index_num()) +
        "|\n"

        "Gdam|Gabacki|Warszawska 47|7|01-234|Warszawa|71030467716|male||" +
        std::to_string(gabacki->salary()) + "\n";

    EXPECT_EQ(db.display(), ref_db_display);
}

TEST_F(DatabaseTest, AssignSalary) {
    EXPECT_EQ(db.assign_salary(Pesel("71030467716"), 7777), true);
    EXPECT_EQ(gabacki->salary(), 7777);
}

TEST_F(DatabaseTest, SaveAndLoad) {
    const auto filepath{"./db.txt"};
    db.save(filepath);

    Database db_from_file;
    db_from_file.load(filepath);

    EXPECT_EQ(db.display(), db_from_file.display());
    EXPECT_EQ(db.content(), db_from_file.content());
}

TEST_F(DatabaseTest, DeleteByIndex) {
    const std::list<const Person*> expected{abacki, babacki, dabacka, fabacki, gabacki};

    const auto person_ptr = db.search_by_pesel(cabacki->pesel()).value();
    auto student_ptr = dynamic_cast<const Student*>(person_ptr);

    db.delete_by_index(student_ptr->index_num());
    EXPECT_EQ(db.content(), expected);
    EXPECT_THROW(db.delete_by_index(3), std::invalid_argument);
}

TEST_F(DatabaseTest, SortByName) {
    std::list<const Person*> expected{abacki, babacki, cabacki, dabacka, fabacki, gabacki};
    db.sort_by_name(Database::SortOrder::Ascending);
    EXPECT_EQ(db.content(), expected);

    expected.reverse();
    db.sort_by_name(Database::SortOrder::Descending);
    EXPECT_EQ(db.content(), expected);
}

TEST_F(DatabaseTest, SortBySalary) {
    std::list<const Person*> expected{gabacki, abacki, babacki, cabacki, dabacka, fabacki};
    db.sort_by_salary(Database::SortOrder::Descending);
    EXPECT_EQ(db.content(), expected);

    expected = {gabacki, abacki, babacki, cabacki, dabacka, fabacki};
    db.sort_by_salary(Database::SortOrder::Ascending);
    EXPECT_EQ(db.content(), expected);
}

TEST_F(DatabaseTest, SortByPesel) {
    std::list<const Person*> expected{dabacka, cabacki, gabacki, babacki, abacki, fabacki};
    db.sort_by_pesel(Database::SortOrder::Ascending);
    EXPECT_EQ(db.content(), expected);

    expected.reverse();
    db.sort_by_pesel(Database::SortOrder::Descending);
    EXPECT_EQ(db.content(), expected);
}

TEST_F(DatabaseTest, SearchByLastName) {
    const auto matches = db.search_by_last_name("Abacki");
    const std::list<const Person*> expected{abacki};

    EXPECT_EQ(matches, expected);
}

TEST_F(DatabaseTest, SearchByPeselFound) {
    const auto match = db.search_by_pesel(Pesel{"55030101193"});
    const auto expected = abacki;

    EXPECT_EQ(match, expected);
}

TEST_F(DatabaseTest, SearchByPeselNotFound) {
    const auto match = db.search_by_pesel(Pesel{"74031288887"});
    const auto expected = std::nullopt;

    EXPECT_EQ(match, expected);
}
