#pragma once

#include <string>

#include "helpers/gender.hpp"
#include "helpers/pesel.hpp"
#include "helpers/random/pseudorandom.hpp"

namespace pseudorandom::personal_data::helpers {
struct BirthDate {
    BirthDate(const uint64_t year, const uint64_t month, const uint64_t day) : m_year(year), m_month(month), m_day(day) {}

    uint64_t m_year;
    uint64_t m_month;
    uint64_t m_day;
};

struct PeselCiphers {
    uint64_t year_cipher_a;
    uint64_t year_cipher_b;

    uint64_t month_cipher_a;
    uint64_t month_cipher_b;

    uint64_t day_cipher_a;
    uint64_t day_cipher_b;

    uint64_t random_nonce_a{random_uint64() % 10ULL};
    uint64_t random_nonce_b{random_uint64() % 10ULL};
    uint64_t random_nonce_c{random_uint64() % 10ULL};

    uint64_t gender_cipher;
    uint64_t checksum_cipher;
};

inline uint64_t random_nonce_for_gender(const Gender gender) {
    if (gender == Gender::Female) {
        return ((random_uint64() % 100ULL) * 2ULL) % 10ULL;
    } else if (gender == Gender::Male) {
        return ((random_uint64() % 100ULL) * 2ULL + 1ULL) % 10ULL;
    }
    return random_uint64() % 10ULL;
}

inline PeselCiphers create_pesel_ciphers(
    const BirthDate birth_date, const Gender gender) {
    auto pesel_ciphers = PeselCiphers{};

    pesel_ciphers.year_cipher_a = (birth_date.m_year % 100ULL) / 10ULL;
    pesel_ciphers.year_cipher_b = birth_date.m_year % 10ULL;

    pesel_ciphers.month_cipher_a = birth_date.m_month / 10ULL;
    pesel_ciphers.month_cipher_b = birth_date.m_month % 10ULL;

    pesel_ciphers.day_cipher_a = birth_date.m_day / 10ULL;
    pesel_ciphers.day_cipher_b = birth_date.m_day % 10ULL;

    pesel_ciphers.gender_cipher = helpers::random_nonce_for_gender(gender);

    return pesel_ciphers;
}

inline void compute_checksum(PeselCiphers& pesel_ciphers) {
    auto sum = (pesel_ciphers.year_cipher_a +
                pesel_ciphers.year_cipher_b * 3ULL +
                pesel_ciphers.month_cipher_a * 7ULL +
                pesel_ciphers.month_cipher_b * 9ULL +
                pesel_ciphers.day_cipher_a +
                pesel_ciphers.day_cipher_b * 3ULL +
                pesel_ciphers.random_nonce_a * 7ULL +
                pesel_ciphers.random_nonce_b * 9ULL +
                pesel_ciphers.random_nonce_c +
                pesel_ciphers.gender_cipher * 3ULL);

    pesel_ciphers.checksum_cipher = (10ULL - (sum % 10ULL)) % 10ULL;
}

inline std::string derive_pesel(const PeselCiphers& pesel_ciphers) {
    std::string pesel{};
    pesel += std::to_string(pesel_ciphers.year_cipher_a);
    pesel += std::to_string(pesel_ciphers.year_cipher_b);
    pesel += std::to_string(pesel_ciphers.month_cipher_a);
    pesel += std::to_string(pesel_ciphers.month_cipher_b);
    pesel += std::to_string(pesel_ciphers.day_cipher_a);
    pesel += std::to_string(pesel_ciphers.day_cipher_b);
    pesel += std::to_string(pesel_ciphers.random_nonce_a);
    pesel += std::to_string(pesel_ciphers.random_nonce_b);
    pesel += std::to_string(pesel_ciphers.random_nonce_c);
    pesel += std::to_string(pesel_ciphers.gender_cipher);
    pesel += std::to_string(pesel_ciphers.checksum_cipher);

    return pesel;
}

inline uint64_t random_day_of_month(const uint64_t year, const uint64_t month) {
    switch (month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return random_uint64() % 31ULL + 1ULL;
    case 2:
        if ((year % 4ULL == 0ULL && year % 100ULL != 0ULL) || (year % 400ULL == 0ULL)) {
            return random_uint64() % 29ULL + 1ULL;
        }
        return random_uint64() % 28ULL + 1ULL;
    default:
        return random_uint64() % 30ULL + 1ULL;
    }
}
}  // namespace pseudorandom::personal_data::helpers

namespace pseudorandom::personal_data {
inline Pesel random_pesel(const Gender gender = Gender::Unspecified) {
    auto random_year = random_uint64() % 100ULL + 1900ULL;
    auto random_month = random_uint64() % 12ULL + 1ULL;
    auto random_day = helpers::random_day_of_month(random_year, random_month);
    auto birth_date = helpers::BirthDate{random_year, random_month, random_day};

    auto pesel_ciphers = helpers::create_pesel_ciphers(birth_date, gender);
    helpers::compute_checksum(pesel_ciphers);

    return Pesel(helpers::derive_pesel(pesel_ciphers));
}
}  // namespace pseudorandom::personal_data
