#include "database.hpp"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "helpers/bytes/tokenize.hpp"

auto Database::add(Student& student) noexcept -> std::optional<Database::ErrorCode> {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        return ErrorCode::StudentAlreadyExistsInDb;
    }
    student.set_index_num(m_curr_index);
    m_state.emplace_back(student);
    ++m_curr_index;
    return std::nullopt;
}

auto Database::add(Student& student, const uint64_t index_num) noexcept -> std::optional<ErrorCode> {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        return ErrorCode::StudentAlreadyExistsInDb;
    }
    student.set_index_num(index_num);
    m_state.emplace_back(student);
    return std::nullopt;
}

auto Database::display(const char sep) const noexcept -> std::string {
    std::string db{""};
    for (const auto& col : columns) {
        db += col;
        db += sep;
    }
    db.back() = '\n';

    for (const auto& student : m_state) {
        auto tokens = tokenize_student(student);
        for (const auto& token : tokens) {
            db += token;
            db += sep;
        }
        db.back() = '\n';
    }
    return db;
}

auto Database::search_by_last_name(const std::string& name) const noexcept -> std::list<Student> {
    std::list<Student> matches;
    for (const auto& student : m_state) {
        if (student.last_name() == name) {
            matches.push_back(student);
        }
    }

    return matches;
}

auto Database::search_by_pesel(const Pesel& pesel) const noexcept -> std::list<Student> {
    std::list<Student> matches;
    for (const auto& student : m_state) {
        if (student.pesel().value() == pesel.value()) {
            matches.push_back(student);
        }
    }

    return matches;
}

// ascending order -> from youngest to oldest
// descending order -> from oldest to youngest
auto Database::sort_by_pesel(const SortOrder order) noexcept -> void {
    if (order == SortOrder::Ascending) {
        m_state.sort([](Student lhs, Student rhs) { return lhs.pesel() < rhs.pesel(); });
    } else {
        m_state.sort([](Student lhs, Student rhs) { return lhs.pesel() > rhs.pesel(); });
    }
}

auto Database::sort_by_name(const SortOrder order) noexcept -> void {
    if (order == SortOrder::Ascending) {
        m_state.sort([](Student lhs, Student rhs) { return (lhs.last_name() < rhs.last_name()); });
    } else {
        m_state.sort([](Student lhs, Student rhs) { return lhs.last_name() > rhs.last_name(); });
    }
}

auto Database::delete_by_index(const uint64_t index) -> std::optional<ErrorCode> {
    for (const auto& student : m_state) {
        if (student.index_num() == index) {
            m_state.remove(student);
            return std::nullopt;
        }
    }
    return ErrorCode::IndexNotFound;
}

auto Database::save(const std::string& filepath, const char sep) const noexcept -> void {
    auto fp = std::filesystem::path(filepath);

    std::ofstream db_file_handler(fp);

    db_file_handler << display(sep);
    db_file_handler.close();
}

auto Database::load(const std::string& filepath, const char sep) -> std::optional<ErrorCode> {
    auto fp = std::filesystem::path(filepath);
    if (!std::filesystem::exists(fp)) {
        return ErrorCode::FilepathDoesNotExist;
    }

    std::ifstream db_file_handler(fp);
    std::string read_line{""};
    std::getline(db_file_handler, read_line, '\n');
    const auto header = bytes::tokenize(read_line, sep);
    if (!std::equal(
            header.begin(), header.end(), columns.begin(), columns.end(),
            [](std::string lhs, std::string_view rhs) { return lhs == rhs; })) {
        return ErrorCode::InvalidHeader;
    }

    auto backup_state = std::list<Student>{};
    m_state.splice(m_state.end(), backup_state);

    while (std::getline(db_file_handler, read_line, '\n')) {
        const auto tokens = bytes::tokenize(read_line, sep);
        auto student = deserialize(tokens);
        const auto read_index_num = std::stoi(tokens[6]);

        const auto it = std::find_if(
            m_state.begin(), m_state.end(),
            [read_index_num](Student student) { return student.index_num() == read_index_num; });

        if (it == m_state.end()) {
            add(student, read_index_num);
        } else {
            backup_state.splice(backup_state.end(), m_state);
            return ErrorCode::DuplicateIndexNum;
        }
    }

    m_curr_index = (std::max_element(
                        m_state.begin(), m_state.end(),
                        [](Student lhs, Student rhs) { return lhs.index_num() < rhs.index_num(); })
                        ->index_num());
    ++m_curr_index;
    db_file_handler.close();

    return std::nullopt;
}

auto Database::deserialize(const std::vector<std::string>& tokens) -> Student {
    const auto first_name = tokens[0];
    const auto last_name = tokens[1];
    const auto address = Address{
        tokens[2], tokens[3], PostalCode{tokens[4]}, tokens[5]};
    const auto pesel = Pesel{tokens[7]};
    const auto gender = parse_gender(tokens[8]);

    return Student{
        first_name, last_name, address, pesel, gender};
}

auto Database::tokenize_student(const Student& student) noexcept -> std::array<std::string, 9> {
    std::array<std::string, 9> tokens;
    tokens[0] = student.first_name();
    tokens[1] = student.last_name();
    tokens[2] = student.address().street();
    tokens[3] = student.address().apartment();
    tokens[4] = student.address().postal_code().value();
    tokens[5] = student.address().city();
    tokens[6] = std::to_string(student.index_num());
    tokens[7] = student.pesel().value();
    tokens[8] = parse_gender(student.gender());

    return tokens;
}

auto parse_database_error_code(Database::ErrorCode error) noexcept -> std::string_view {
    switch (error) {
    case Database::ErrorCode::StudentAlreadyExistsInDb:
        return "student already exists in database";
    case Database::ErrorCode::IndexNotFound:
        return "could not find student with provided index";
    case Database::ErrorCode::FilepathDoesNotExist:
        return "provided filepath to database file does not exist";
    case Database::ErrorCode::InvalidHeader:
        return "could not read properly column names from database file";
    case Database::ErrorCode::DuplicateIndexNum:
        return "encountered the same index number more than once in database file";
    default:
        return "ok";
    }
}
