#pragma once
#include <list>
#include <optional>
#include "student.hpp"

class Database {
public:
    enum class ErrorCode {
        StudentAlreadyExistsInDb
    };
    auto add(const Student& student) -> std::optional<ErrorCode>;

private:
    std::list<Student> m_state;
};

auto parse_database_error_code(Database::ErrorCode error) -> std::string_view;
