#pragma once
#include <array>
#include <cstdint>
#include <list>
#include <optional>
#include <string_view>
#include <vector>

#include "student.hpp"

class Database {
public:
    enum class ErrorCode {
        StudentAlreadyExistsInDb,
        IndexNotFound,
        FilepathDoesNotExist,
        InvalidHeader,
        DuplicateIndexNum
    };

    enum class SortOrder {
        Ascending,
        Descending
    };

    auto add(Student& student) noexcept -> std::optional<ErrorCode>;
    auto display(const char sep = '|') const noexcept -> std::string;
    auto search_by_last_name(const std::string& name) const noexcept -> std::list<Student>;
    auto search_by_pesel(const Pesel& pesel) const noexcept -> std::list<Student>;
    auto sort_by_pesel(const SortOrder order = SortOrder::Ascending) noexcept -> void;
    auto sort_by_name(const SortOrder order = SortOrder::Ascending) noexcept -> void;
    auto delete_by_index(const uint64_t index) -> std::optional<ErrorCode>;
    auto save(const std::string& filepath, const char sep = '|') const noexcept -> void;
    auto load(const std::string& filepath, const char sep = '|') -> std::optional<ErrorCode>;

    auto students() const noexcept -> const std::list<Student>& { return m_state; }

    static auto tokenize_student(const Student& student) noexcept -> std::array<std::string, 9>;
    static auto deserialize(const std::vector<std::string>& tokens) -> Student;

    static constexpr std::array<std::string_view, 9> columns{
        "first_name", "last_name", "street", "apartment", "postal_code", "city", "index_num", "pesel", "gender"};

private:
    auto add(Student& student, const uint64_t index_num) noexcept -> std::optional<ErrorCode>;

    std::list<Student> m_state;
    uint64_t m_curr_index = 1ULL;
};

auto parse_database_error_code(Database::ErrorCode error) noexcept -> std::string_view;
