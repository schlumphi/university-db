#pragma once

#include <string>

#include "helpers/address.hpp"
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

inline constexpr std::array<std::string_view, 22> male_names{
    "Adam",
    "Bartosz",
    "Cyprian",
    "Dawid",
    "Eustachy",
    "Filip",
    "Grzegorz",
    "Henryk",
    "Ignacy",
    "Jakub",
    "Krzysztof",
    "Lucjan",
    "Mariusz",
    "Nataniel",
    "Olaf",
    "Patryk",
    "Ryszard",
    "Szymon",
    "Tomasz",
    "Udalryk",
    "Wojciech",
    "Zenon"};

inline constexpr std::array<std::string_view, 22> female_names{
    "Alicja",
    "Beata",
    "Celestyna",
    "Daria",
    "Ewa",
    "Flora",
    "Gabriela",
    "Helena",
    "Izabela",
    "Jagna",
    "Karolina",
    "Lidia",
    "Maria",
    "Nadia",
    "Otylia",
    "Petra",
    "Roksana",
    "Sabina",
    "Teresa",
    "Urszula",
    "Wanda",
    "Zuzanna"};

inline constexpr std::array<std::string_view, 22> male_surnames{
    "Adamski",
    "Bartecki",
    "Cygan",
    "Dopieralski",
    "Engel",
    "Firlej",
    "Gonciarz",
    "Hula",
    "Iwanejko",
    "Jaroszewski",
    "Kordela",
    "Luty",
    "Marzec",
    "Najdowski",
    "Ostaszewski",
    "Przybylski",
    "Raszewski",
    "Stoch",
    "Tuwim",
    "Ulam",
    "Wirecki",
    "Zawada"};

inline constexpr std::array<std::string_view, 22> female_surnames{
    "Adamska",
    "Bartecka",
    "Cygan",
    "Dopieralska",
    "Engel",
    "Firlej",
    "Gonciarz",
    "Hula",
    "Iwanejko",
    "Jaroszewska",
    "Kordela",
    "Luty",
    "Marzec",
    "Najdowska",
    "Ostaszewska",
    "Przybylska",
    "Raszewska",
    "Stoch",
    "Tuwim",
    "Ulam",
    "Wirecka",
    "Zawada"};

inline constexpr std::array<std::string_view, 22> street_names{
    "Analogowa",
    "Bajkowa",
    "Cesarska",
    "Daliowa",
    "Ekologiczna",
    "Franciszka Augusta",
    "Gagarina",
    "Huncwocka",
    "Izydora",
    "Jarzynowa",
    "Koluszki",
    "Lazurowa",
    "Marzycielska",
    "Nostradamusa",
    "Opolska",
    "Plac Trzech Krzyzy",
    "Ratuszowa",
    "Stalowej Woli",
    "Torwar",
    "Ugory",
    "Wysoka",
    "Zacisze"};

inline constexpr std::array<std::string_view, 22> cities{
    "Augustow",
    "Bydgoszcz",
    "Chelm",
    "Debica",
    "Elblag",
    "Frombork",
    "Gdansk",
    "Hel",
    "Inowroclaw",
    "Jaslo",
    "Krakow",
    "Lublin",
    "Malbork",
    "Nowy Sacz",
    "Olsztyn",
    "Poznan",
    "Rzeszow",
    "Sopot",
    "Torun",
    "Ustka",
    "Warszawa",
    "Zamosc"};

inline PostalCode random_postal_code() {
    return PostalCode{
        std::to_string(pseudorandom::random_uint64() % 10ULL) +
        std::to_string(pseudorandom::random_uint64() % 10ULL) +
        "-" +
        std::to_string(pseudorandom::random_uint64() % 10ULL) +
        std::to_string(pseudorandom::random_uint64() % 10ULL) +
        std::to_string(pseudorandom::random_uint64() % 10ULL)};
}

inline std::string random_apartment_number() {
    auto number = pseudorandom::random_uint64() % 1000ULL;
    if (number == 0ULL) {
        return "";
    } else {
        return std::to_string(number);
    }
}
}  // namespace pseudorandom::personal_data::helpers

namespace pseudorandom::personal_data {
inline Gender random_gender() {
    auto rand_num = pseudorandom::random_uint64() % 2ULL;
    if (rand_num == 0ULL) {
        return Gender::Male;
    } else {
        return Gender::Female;
    }
}

// FIXME: dodac obsluge wszystkich zakresow peseli
inline Pesel random_pesel(const Gender gender = Gender::Unspecified) {
    auto random_year = random_uint64() % 100ULL + 1900ULL;
    auto random_month = random_uint64() % 12ULL + 1ULL;
    auto random_day = helpers::random_day_of_month(random_year, random_month);
    auto birth_date = helpers::BirthDate{random_year, random_month, random_day};

    auto pesel_ciphers = helpers::create_pesel_ciphers(birth_date, gender);
    helpers::compute_checksum(pesel_ciphers);

    return Pesel(helpers::derive_pesel(pesel_ciphers));
}

inline std::string random_name(const Gender gender = Gender::Unspecified) {
    if (gender == Gender::Male) {
        return static_cast<std::string>(helpers::male_names[pseudorandom::random_uint64() % helpers::male_names.size()]);
    } else if (gender == Gender::Female) {
        return static_cast<std::string>(helpers::female_names[pseudorandom::random_uint64() % helpers::female_names.size()]);
    } else {
        std::array<std::string_view, 44> names;
        std::copy(helpers::male_names.begin(), helpers::male_names.end(), names.begin());
        std::copy(helpers::female_names.begin(), helpers::female_names.end(), names.begin() + helpers::male_names.size());
        return static_cast<std::string>(names[pseudorandom::random_uint64() % names.size()]);
    }
}

inline std::string random_surname(const Gender gender = Gender::Unspecified) {
    if (gender == Gender::Male) {
        return static_cast<std::string>(helpers::male_surnames[pseudorandom::random_uint64() % helpers::male_names.size()]);
    } else if (gender == Gender::Female) {
        return static_cast<std::string>(helpers::female_surnames[pseudorandom::random_uint64() % helpers::female_names.size()]);
    } else {
        std::array<std::string_view, 44> surnames;
        std::copy(helpers::male_surnames.begin(), helpers::male_surnames.end(), surnames.begin());
        std::copy(helpers::female_surnames.begin(), helpers::female_surnames.end(), surnames.begin() + helpers::male_surnames.size());
        return static_cast<std::string>(surnames[pseudorandom::random_uint64() % surnames.size()]);
    }
}

inline Address random_address() {
    return Address{
        std::string{helpers::street_names.at(pseudorandom::random_uint64() % helpers::street_names.size())} + " " + std::to_string(pseudorandom::random_uint64() % 1000ULL + 1ULL),
        helpers::random_apartment_number(),
        helpers::random_postal_code(),
        std::string{helpers::cities.at(pseudorandom::random_uint64() % helpers::cities.size())}};
}
}  // namespace pseudorandom::personal_data
