#include "address.hpp"

Address::Address(
    std::string_view street,
    std::string_view apartment,
    const PostalCode& postal_code,
    std::string_view city)
    : m_street(street), m_apartment(apartment), m_postal_code(postal_code), m_city(city) {
}
