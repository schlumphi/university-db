#pragma once
#include <iostream>

enum class Gender {
    Male,
    Female,
    Unspecified
};

inline std::string parse_gender(const Gender gender) noexcept {
    if (gender == Gender::Male) {
        return "male";
    } else if (gender == Gender::Female) {
        return "female";
    } else {
        return "unspecified";
    }
}

inline Gender parse_gender(const std::string& gender) {
    if (gender == "male") {
        return Gender::Male;
    } else if (gender == "female") {
        return Gender::Female;
    } else {
        return Gender::Unspecified;
    }
}
