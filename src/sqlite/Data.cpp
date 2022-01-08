#include "Data.hpp"

using namespace SQLite::Impl_;

Data::Data(const int cols, char** const values, char** const keys) noexcept {

    keys_.reserve(cols);
    values_.reserve(cols);

    for (auto i = 0, end = cols; i < end; ++i) {
        keys_.emplace_back(keys[i]);
        values_.emplace_back(values[i] == nullptr ? std::optional<std::string>{} : values[i]);
    }
}
