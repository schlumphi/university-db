#pragma once
#include "person.hpp"

class Database;

class NullPerson : public Person {
public:
    virtual bool is_null() const noexcept override { return true; }
};
