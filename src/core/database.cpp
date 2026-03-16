#include "database.hpp"
#include <algorithm>

auto Database::add(Student& student) noexcept -> std::optional<Database::ErrorCode> {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        return ErrorCode::StudentAlreadyExistsInDb;
    }
    student.set_index_num(m_curr_index);
    m_state.emplace_back(student);
    ++m_curr_index;
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
        m_state.sort([](Student lhs, Student rhs) { return (lhs.pesel() < rhs.pesel()); });
    } else {
        m_state.sort([](Student lhs, Student rhs) { return !(lhs.pesel() < rhs.pesel()); });
    }
}

auto Database::sort_by_name(const SortOrder order) noexcept -> void {
    if (order == SortOrder::Ascending) {
        m_state.sort([](Student lhs, Student rhs) { return (lhs.last_name() < rhs.last_name()); });
    } else {
        m_state.sort([](Student lhs, Student rhs) { return lhs.last_name() > rhs.last_name(); });
    }
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
    default:
        return "ok";
    }
}
