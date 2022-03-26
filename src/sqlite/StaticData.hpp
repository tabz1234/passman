#pragma once

#include <array>
#include <optional>
#include <string>

#include "impl/Data_tag.hpp"

namespace SQLite {
    template <int TableSZ>
    struct StaticData final : Impl_::Data_tag {

        std::array<std::string, TableSZ> keys_;
        std::array<std::optional<std::string>, TableSZ> values_;

        StaticData(char** const values, char** const keys) noexcept
        {
            for (int i = 0; i < TableSZ; ++i) {
                keys_[i] = keys[i];
                values_[i] = values[i] == nullptr ? std::optional<std::string>{} : values[i];
            }
        }
    };

} // namespace SQLite
