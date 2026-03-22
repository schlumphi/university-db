#pragma once
#include <iostream>

enum class Gender {
    Male,
    Female
};

inline std::string parse_gender(const Gender gender) noexcept {
    if (gender == Gender::Male) {
        return "male";
    } else {
        return "female";
    }
}

inline Gender parse_gender(const std::string& gender) {
    if (gender == "male") {
        return Gender::Male;
    } else if (gender == "female") {
        return Gender::Female;
    } else {
        throw std::invalid_argument("expected 'gender' to be 'male' or 'female'");
    }
}
