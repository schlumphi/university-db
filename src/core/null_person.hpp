#pragma once
#include "person.hpp"

class Database;

class NullPerson : public Person {
public:
    NullPerson() : Person("Null", "Null", Address::null(), Pesel::null(), Gender::Unspecified) {}

    virtual bool is_null() const noexcept override { return true; }
};
