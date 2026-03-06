#include "database.hpp"
#include <algorithm>

auto Database::add(const Student& student) -> bool {
    if (std::find(m_state.begin(), m_state.end(), student) != m_state.end()) {
        return false;
    }
    m_state.emplace_back(student);
    return true;
}
