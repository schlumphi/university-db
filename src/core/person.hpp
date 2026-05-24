#pragma once

#include "helpers/address.hpp"
#include "helpers/gender.hpp"
#include "helpers/pesel.hpp"

class Person {
public:
    virtual ~Person() = default;

    bool operator==(const Person& other) const noexcept {
        if (other.m_pesel.value() == m_pesel.value()) {
            return true;
        }
        return false;
    }

    const std::string&
    first_name() const noexcept {
        return m_first_name;
    }
    const std::string& last_name() const noexcept { return m_last_name; }
    const Address& address() const noexcept { return m_address; }
    const Pesel& pesel() const noexcept { return m_pesel; }
    Gender gender() const noexcept { return m_gender; }

    static std::string validate_name(const std::string& name);
    static Gender validate_gender(const Pesel& pesel, const Gender gender);

protected:
    Person(const std::string& first_name,
           const std::string& last_name,
           const Address& address,
           const Pesel& pesel,
           const Gender gender);

    const std::string m_first_name;
    const std::string m_last_name;
    const Address m_address;
    const Pesel m_pesel;
    const Gender m_gender;
};
