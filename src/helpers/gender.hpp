#pragma once
#include <iostream>

enum class Gender {
    Male,
    Female
};

inline auto parse_gender(const Gender gender) noexcept -> std::string {
    if (gender == Gender::Male) {
        return "male";
    } else {
        return "female";
    }
}

inline auto parse_gender(const std::string& gender) -> Gender {
    if (gender == "male") {
        return Gender::Male;
    } else if (gender == "female") {
        return Gender::Female;
    } else {
        throw std::invalid_argument("expected 'gender' to be 'male' or 'female'");
    }
}
