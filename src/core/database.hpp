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
    enum class SortOrder {
        Ascending,
        Descending
    };

    void add(Student& student);
    std::string display(const char sep = '|') const noexcept;
    std::list<Student> search_by_last_name(const std::string& name) const noexcept;
    std::optional<Student> search_by_pesel(const Pesel& pesel) const noexcept;
    void sort_by_pesel(const SortOrder order = SortOrder::Ascending) noexcept;
    void sort_by_name(const SortOrder order = SortOrder::Ascending) noexcept;
    void delete_by_index(const uint64_t index);
    void save(const std::string& filepath, const char sep = '|') const noexcept;
    void load(const std::string& filepath, const char sep = '|');

    const std::list<Student>& students() const noexcept { return m_state; }

    static std::array<std::string, 9> tokenize_student(const Student& student) noexcept;
    static Student deserialize(const std::vector<std::string_view>& tokens);

    static constexpr std::array<std::string_view, 9> columns{
        "first_name", "last_name", "street", "apartment", "postal_code", "city", "index_num", "pesel", "gender"};

private:
    void add(Student& student, const uint64_t index_num);

    std::list<Student> m_state;
    uint64_t m_curr_index = 1ULL;
};
