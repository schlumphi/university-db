#pragma once
#include <array>
#include <cstdint>
#include <list>
#include <optional>
#include <string_view>
#include "student.hpp"

class Database {
public:
    enum class ErrorCode {
        StudentAlreadyExistsInDb
    };

    auto add(Student& student) noexcept -> std::optional<ErrorCode>;
    auto display(const char sep = '|') const noexcept -> std::string;
    auto search_by_last_name(const std::string& name) const noexcept -> std::list<Student>;
    auto search_by_pesel(const Pesel& pesel) const noexcept -> std::list<Student>;

    static auto parse_student(const Student& student) noexcept -> std::array<std::string, 9>;

    static constexpr std::array<std::string_view, 9> columns{
        "first_name", "last_name", "street", "apartment", "postal_code", "city", "index_num", "pesel", "gender"};

private:
    std::list<Student> m_state;
    uint64_t m_curr_index = 1ULL;
};

auto parse_database_error_code(Database::ErrorCode error) noexcept -> std::string_view;
