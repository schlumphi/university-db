#include "address.hpp"

Address::Address(
    const std::string& street,
    const std::string& apartment,
    const PostalCode& postal_code,
    const std::string& city)
    : m_street(street), m_apartment(apartment), m_postal_code(postal_code), m_city(city) {
}
