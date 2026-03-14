#include "database.hpp"
#include <algorithm>

auto Database::add(const Student& student) noexcept -> std::optional<Database::ErrorCode> {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        return ErrorCode::StudentAlreadyExistsInDb;
    }
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
        auto tokens = parse_student(student);
        for (const auto& token : tokens) {
            db += token;
            db += sep;
        }
        db.back() = '\n';
    }
    return db;
}

auto Database::parse_student(const Student& student) noexcept -> std::array<std::string, 9> {
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
