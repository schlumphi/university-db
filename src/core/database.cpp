#include "database.hpp"
#include <algorithm>

auto Database::add(const Student& student) -> std::optional<Database::ErrorCode> {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        return ErrorCode::StudentAlreadyExistsInDb;
    }
    m_state.emplace_back(student);
    return std::nullopt;
}

auto parse_database_error_code(Database::ErrorCode error) -> std::string_view {
    switch (error) {
    case Database::ErrorCode::StudentAlreadyExistsInDb:
        return "student already exists in database";
    default:
        return "ok";
    }
}
