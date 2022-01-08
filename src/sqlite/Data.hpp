#pragma once

#include <optional>
#include <string>
#include <vector>

namespace SQLite {
    namespace Impl_ {
        struct Data final {

            std::vector<std::string> keys_;
            std::vector<std::optional<std::string>> values_;

            Data(const int cols, char** const values, char** const keys) noexcept;
        };
    } // namespace Impl_
} // namespace SQLite
