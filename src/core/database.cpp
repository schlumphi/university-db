#include "database.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "helpers/bytes/tokenize.hpp"

void Database::add(Student& student) {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        throw std::invalid_argument("student already exists in database");
    }
    student.set_index_num(m_curr_index);
    m_state.emplace_back(student);
    ++m_curr_index;
}

void Database::add(Student& student, const uint64_t index_num) {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        throw std::invalid_argument("student already exists in database");
    }
    if (is_index_taken(index_num)) {
        throw std::invalid_argument("provided 'index_num' is already assigned to another student");
    }
    student.set_index_num(index_num);
    m_state.emplace_back(student);
}

bool Database::is_index_taken(const uint64_t index_num) const noexcept {
    const auto it = std::find_if(
        m_state.begin(), m_state.end(),
        [index_num](Student student) { return student.index_num() == index_num; });

    if (it != m_state.end()) {
        return true;
    } else {
        return false;
    }
}

// FIXME: disperse into smaller private methods
std::string Database::display(const char sep) const noexcept {
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

std::list<Student> Database::search_by_last_name(const std::string& name) const noexcept {
    std::list<Student> matches;
    for (const auto& student : m_state) {
        if (student.last_name() == name) {
            matches.push_back(student);
        }
    }

    return matches;
}

std::optional<Student> Database::search_by_pesel(const Pesel& pesel) const noexcept {
    for (const auto& student : m_state) {
        if (student.pesel().value() == pesel.value()) {
            return student;
        }
    }

    return std::nullopt;
}

// ascending order -> from youngest to oldest
// descending order -> from oldest to youngest
void Database::sort_by_pesel(const SortOrder order) noexcept {
    if (order == SortOrder::Ascending) {
        m_state.sort([](Student lhs, Student rhs) { return lhs.pesel() < rhs.pesel(); });
    } else {
        m_state.sort([](Student lhs, Student rhs) { return lhs.pesel() > rhs.pesel(); });
    }
}

void Database::sort_by_name(const SortOrder order) noexcept {
    if (order == SortOrder::Ascending) {
        m_state.sort([](Student lhs, Student rhs) { return (lhs.last_name() < rhs.last_name()); });
    } else {
        m_state.sort([](Student lhs, Student rhs) { return lhs.last_name() > rhs.last_name(); });
    }
}

void Database::delete_by_index(const uint64_t index) {
    for (const auto& student : m_state) {
        if (student.index_num() == index) {
            m_state.remove(student);
            return;
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

void Database::load(const std::string& filepath, const char sep) {
    const auto fp = std::filesystem::path(filepath);
    if (!std::filesystem::exists(fp)) {
        throw std::invalid_argument("provided filepath to database file does not exist");
    }

    std::ifstream db_file_handler(fp);
    std::string read_line{""};

    std::getline(db_file_handler, read_line, '\n');
    validate_loaded_header(read_line, sep);

    auto backup_state = std::list<Student>{};
    m_state.splice(backup_state.begin(), m_state);

    while (std::getline(db_file_handler, read_line, '\n')) {
        try {
            load_student_record(read_line);
        } catch (std::invalid_argument const& error) {
            m_state.clear();
            backup_state.splice(m_state.begin(), backup_state);
            throw std::runtime_error(error.what());
        }
    }

    reset_current_index_number();
    db_file_handler.close();
}

void Database::validate_loaded_header(const std::string& header, const char sep) const {
    const auto header_tokens = bytes::tokenize(header, sep);
    if (!std::equal(
            header_tokens.begin(), header_tokens.end(), columns.begin(), columns.end(),
            [](std::string_view lhs, std::string_view rhs) { return lhs == rhs; })) {
        throw std::runtime_error("the header from the loaded database is incorrect");
    }
}

void Database::load_student_record(const std::string& student_record_line, const char sep) {
    const auto tokens = bytes::tokenize(student_record_line, sep);
    auto student = deserialize(tokens);
    const auto read_index_num = static_cast<uint64_t>(std::stoi(std::string(tokens[6])));

    add(student, read_index_num);
}

uint64_t Database::find_highest_index_num() const noexcept {
    if (m_state.empty()) {
        return 0ULL;
    } else {
        return (std::max_element(
                    m_state.begin(), m_state.end(),
                    [](Student lhs, Student rhs) { return lhs.index_num() < rhs.index_num(); })
                    ->index_num());
    }
}

void Database::reset_current_index_number() noexcept {
    m_curr_index = find_highest_index_num();
    ++m_curr_index;
}

Student Database::deserialize(const std::vector<std::string_view>& tokens) {
    const auto first_name = std::string(tokens[0]);
    const auto last_name = std::string(tokens[1]);
    const auto address = Address{
        std::string(tokens[2]), std::string(tokens[3]), PostalCode{std::string(tokens[4])}, std::string(tokens[5])};
    const auto pesel = Pesel{std::string(tokens[7])};
    const auto gender = parse_gender(std::string(tokens[8]));

    return Student{
        first_name, last_name, address, pesel, gender};
}

std::array<std::string, 9> Database::tokenize_student(const Student& student) noexcept {
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
