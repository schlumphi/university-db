#pragma once
#include <list>
#include "student.hpp"

class Database {
public:
    auto add(const Student& student) -> bool;

private:
    std::list<Student> m_state;
};
