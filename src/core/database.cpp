#include "database.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "helpers/bytes/tokenize.hpp"
#include "helpers/random/personal_data.hpp"
#include "helpers/random/pseudorandom.hpp"

const Person* Database::find_by_pesel(const Pesel& pesel) const noexcept {
    for (const auto& person_ptr : m_state) {
        if (person_ptr->pesel().value() == pesel.value()) {
            return person_ptr.get();
        }
    }
    return nullptr;
}

bool Database::exists(const Person& person) const noexcept {
    if (find_by_pesel(person.pesel()) != nullptr) {
        return true;
    } else {
        return false;
    }
}

void Database::add(std::unique_ptr<Person> person) {
    if (exists(*person)) {
        throw std::runtime_error("person already exists in database");
    }

    if (auto student = dynamic_cast<Student*>(person.get())) {
        student->set_index_num(generate_index_num());
    } else if (auto employee = dynamic_cast<Employee*>(person.get())) {
        assign_starting_salary(*employee);
    }

    m_state.push_back(std::move(person));
}

Person* Database::find_by_pesel(const Pesel& pesel) noexcept {
    for (const auto& person_ptr : m_state) {
        if (person_ptr->pesel().value() == pesel.value()) {
            return person_ptr.get();
        }
    }
    return nullptr;
}

bool Database::is_index_taken(const uint64_t index_num) const noexcept {
    for (const auto& person_ptr : m_state) {
        if (auto student = dynamic_cast<Student*>(person_ptr.get())) {
            if (student->index_num() == index_num) {
                return true;
            }
        }
    }
    return false;
}

uint64_t Database::generate_index_num() const noexcept {
    auto index_num = m_state.size() + static_cast<uint64_t>(pseudorandom::random_uint32());
    while (is_index_taken(index_num)) {
        index_num = m_state.size() + static_cast<uint64_t>(pseudorandom::random_uint32());
    }
    return index_num;
}

void Database::assign_starting_salary(Employee& employee) {
    auto salary = pseudorandom::random_uint64(4500ULL, 10000ULL);
    employee.set_salary(salary);
}

bool Database::assign_salary(const Pesel& pesel, const uint64_t salary) noexcept {
    auto* person = find_by_pesel(pesel);
    if (person == nullptr) {
        return false;
    }

    if (auto employee = dynamic_cast<Employee*>(person)) {
        employee->set_salary(salary);
        return true;
    }
    return false;
}

// bool Database::is_index_taken(const uint64_t index_num) const noexcept {
//     const auto it = std::find_if(
//         m_state.begin(), m_state.end(),
//         [index_num](Student student) { return student.index_num() == index_num; });

//     if (it != m_state.end()) {
//         return true;
//     } else {
//         return false;
//     }
// }

std::string Database::display(const char sep) const noexcept {
    std::string db{""};
    for (const auto& col : columns) {
        db += col;
        db += sep;
    }
    db.back() = '\n';

    for (const auto& person_ptr : m_state) {
        for (const auto& token : person_ptr->tokenize()) {
            db += token;
            db += sep;
        }
        db.back() = '\n';
    }
    return db;
}

// FIXME:
void Database::fill_with_random_data(const uint64_t records_amount) {
    size_t i = 0;
    while (i < records_amount) {
        auto random_number = pseudorandom::random_uint64(0, 5);
        if (random_number == 0ULL) {
            auto employee = std::make_unique<Employee>(Employee::random_employee());
            try {
                add(std::move(employee));
                ++i;
            } catch (const std::runtime_error& error) {
            }
        } else {
            auto student = std::make_unique<Student>(Student::random_student());
            try {
                add(std::move(student));
                ++i;
            } catch (const std::runtime_error& error) {
            }
        }
    }
}

std::list<const Person*> Database::search_by_last_name(const std::string& name) const noexcept {
    std::list<const Person*> matches{};
    for (const auto& person_ptr : m_state) {
        if (person_ptr->last_name() == name) {
            matches.push_back(person_ptr.get());
        }
    }

    return matches;
}

std::optional<const Person*> Database::search_by_pesel(const Pesel& pesel) const noexcept {
    for (const auto& person_ptr : m_state) {
        if (person_ptr->pesel().value() == pesel.value()) {
            return person_ptr.get();
        }
    }

    return std::nullopt;
}

// ascending order -> from youngest to oldest
// descending order -> from oldest to youngest
void Database::sort_by_pesel(const SortOrder order) noexcept {
    if (order == SortOrder::Ascending) {
        m_state.sort([](std::unique_ptr<Person>& lhs, std::unique_ptr<Person>& rhs) { return lhs->pesel() < rhs->pesel(); });
    } else {
        m_state.sort([](std::unique_ptr<Person>& lhs, std::unique_ptr<Person>& rhs) { return lhs->pesel() > rhs->pesel(); });
    }
}

void Database::sort_by_name(const SortOrder order) noexcept {
    if (order == SortOrder::Ascending) {
        m_state.sort([](std::unique_ptr<Person>& lhs, std::unique_ptr<Person>& rhs) { return (lhs->last_name() < rhs->last_name()); });
    } else {
        m_state.sort([](std::unique_ptr<Person>& lhs, std::unique_ptr<Person>& rhs) { return lhs->last_name() > rhs->last_name(); });
    }
}

void Database::sort_by_salary(const SortOrder order) noexcept {
    if (order == SortOrder::Ascending) {
        sort_by_salary_asc();
    } else {
        sort_by_salary_desc();
    }
}

void Database::sort_by_salary_asc() noexcept {
    m_state.sort([](std::unique_ptr<Person>& lhs, std::unique_ptr<Person>& rhs) {
        auto first_employee = dynamic_cast<Employee*>(lhs.get());
        auto second_employee = dynamic_cast<Employee*>(rhs.get());
        if (first_employee && second_employee) {
            return first_employee->salary() < second_employee->salary();
        } else if (first_employee) {
            return true;
        } else if (second_employee) {
            return false;
        } else {
            return false;
        }
    });
}

void Database::sort_by_salary_desc() noexcept {
    m_state.sort([](std::unique_ptr<Person>& lhs, std::unique_ptr<Person>& rhs) {
        auto first_employee = dynamic_cast<Employee*>(lhs.get());
        auto second_employee = dynamic_cast<Employee*>(rhs.get());
        if (first_employee && second_employee) {
            return first_employee->salary() > second_employee->salary();
        } else if (first_employee) {
            return true;
        } else if (second_employee) {
            return false;
        } else {
            return false;
        }
    });
}

std::list<const Person*> Database::content() const noexcept {
    auto state = std::list<const Person*>{};
    for (const auto& person_ptr : m_state) {
        state.push_back(person_ptr.get());
    }
    return state;
}

void Database::delete_by_index(const uint64_t index) {
    for (const auto& person_ptr : m_state) {
        if (auto student = dynamic_cast<Student*>(person_ptr.get())) {
            if (student->index_num() == index) {
                m_state.remove(person_ptr);
                return;
            }
        }
    }

    throw std::invalid_argument("could not find student with provided index");
}

void Database::save(const std::string& filepath, const char sep) const noexcept {
    const auto fp = std::filesystem::path(filepath);

    std::ofstream db_file_handler(fp);

    db_file_handler << display(sep);
    db_file_handler.close();
}

// void Database::load(const std::string& filepath, const char sep) {
//     const auto fp = std::filesystem::path(filepath);
//     if (!std::filesystem::exists(fp)) {
//         throw std::invalid_argument("provided filepath to database file does not exist");
//     }

//     std::ifstream db_file_handler(fp);
//     std::string read_line{""};

//     std::getline(db_file_handler, read_line, '\n');
//     validate_loaded_header(read_line, sep);

//     auto backup_state = std::list<Student>{};
//     m_state.splice(backup_state.begin(), m_state);

//     while (std::getline(db_file_handler, read_line, '\n')) {
//         try {
//             load_student_record(read_line);
//         } catch (std::invalid_argument const& error) {
//             m_state.clear();
//             backup_state.splice(m_state.begin(), backup_state);
//             throw std::runtime_error(error.what());
//         }
//     }

//     reset_current_index_number();
//     db_file_handler.close();
// }

// void Database::validate_loaded_header(const std::string& header, const char sep) const {
//     const auto header_tokens = bytes::tokenize(header, sep);
//     if (!std::equal(
//             header_tokens.begin(), header_tokens.end(), columns.begin(), columns.end(),
//             [](std::string_view lhs, std::string_view rhs) { return lhs == rhs; })) {
//         throw std::runtime_error("the header from the loaded database is incorrect");
//     }
// }

// void Database::load_student_record(const std::string& student_record_line, const char sep) {
//     const auto tokens = bytes::tokenize(student_record_line, sep);
//     auto student = deserialize(tokens);
//     const auto read_index_num = static_cast<uint64_t>(std::stoi(std::string(tokens[6])));

//     add(student, read_index_num);
// }

// Student Database::deserialize(const std::vector<std::string_view>& tokens) {
//     const auto first_name = std::string(tokens[0]);
//     const auto last_name = std::string(tokens[1]);
//     const auto address = Address{
//         std::string(tokens[2]), std::string(tokens[3]), PostalCode{std::string(tokens[4])}, std::string(tokens[5])};
//     const auto pesel = Pesel{std::string(tokens[7])};
//     const auto gender = parse_gender(std::string(tokens[8]));

//     return Student{
//         first_name, last_name, address, pesel, gender};
// }

std::array<std::string, 10> Database::tokenize(const Person* person) noexcept {
    std::array<std::string, 10> tokens;
    tokens[0] = person->first_name();
    tokens[1] = person->last_name();
    tokens[2] = person->address().street();
    tokens[3] = person->address().apartment();
    tokens[4] = person->address().postal_code().value();
    tokens[5] = person->address().city();
    const auto student_ptr = dynamic_cast<const Student*>(person);
    if (student_ptr) {
        tokens[6] = std::to_string(student_ptr->index_num());
    } else {
        tokens[6] = "";
    }
    tokens[7] = person->pesel().value();
    tokens[8] = parse_gender(person->gender());

    const auto employee_ptr = dynamic_cast<const Employee*>(person);
    if (employee_ptr) {
        tokens[9] = std::to_string(employee_ptr->salary());
    } else {
        tokens[9] = "";
    }

    return tokens;
}
