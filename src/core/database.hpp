#pragma once
#include <array>
#include <cstdint>
#include <list>
#include <memory>
#include <optional>
#include <string_view>
#include <vector>

#include "employee.hpp"
#include "person.hpp"
#include "student.hpp"

class Database {
public:
    enum class SortOrder {
        Ascending,
        Descending
    };

    void add(std::unique_ptr<Person> person);
    const Person* find_by_pesel(const Pesel& pesel) const noexcept;
    bool exists(const Person& person) const noexcept;
    uint64_t generate_index_num() const noexcept;
    bool is_index_taken(const uint64_t index_num) const noexcept;

    std::string display(const char sep = '|') const noexcept;

    void fill_with_random_data(const uint64_t records_amount);

    bool assign_salary(const Pesel& pesel, const uint64_t salary) noexcept;
    std::list<const Person*> search_by_last_name(const std::string& name) const noexcept;
    std::optional<const Person*> search_by_pesel(const Pesel& pesel) const noexcept;
    void sort_by_pesel(const SortOrder order = SortOrder::Ascending) noexcept;
    void sort_by_name(const SortOrder order = SortOrder::Ascending) noexcept;
    void sort_by_salary(const SortOrder order = SortOrder::Ascending) noexcept;

    std::list<const Person*> content() const noexcept;

    void delete_by_index(const uint64_t index);
    void save(const std::string& filepath, const char sep = '|') const noexcept;
    void load(const std::string& filepath, const char sep = '|');

    static std::array<std::string, 10> tokenize(const Person* person) noexcept;
    static std::unique_ptr<Person> deserialize(const std::vector<std::string_view>& tokens);

    static constexpr std::array<std::string_view, 10> columns{
        "first_name", "last_name", "street", "apartment", "postal_code", "city", "pesel", "gender", "index_num", "salary"};

private:
    Person* find_by_pesel(const Pesel& pesel) noexcept;
    void assign_starting_salary(Employee& employee);
    void sort_by_salary_asc() noexcept;
    void sort_by_salary_desc() noexcept;
    void validate_loaded_header(const std::string& header, const char sep = '|') const;
    void add_direct(std::unique_ptr<Person> person);
    void load_record(const std::string& record_line, const char sep = '|');

    std::list<std::unique_ptr<Person>> m_state;
};
