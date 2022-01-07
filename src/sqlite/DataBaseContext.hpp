#pragma once

struct sqlite3;

#include <string_view>

#include "Data.hpp"

namespace SQLite {
    namespace Impl_ {
        struct DataBaseContext final { // unique ptr is not the case here

            explicit DataBaseContext(const std::string_view dbpath);

            sqlite3* ptr() noexcept;

            ~DataBaseContext();

          private:
            sqlite3* raw_ctx_;

          public:
            DataBaseContext(const DataBaseContext&) = delete;
            DataBaseContext& operator=(const DataBaseContext&) = delete;

            DataBaseContext(DataBaseContext&&) = delete;
            DataBaseContext& operator=(DataBaseContext&&) = delete;
        };
    } // namespace Impl_
} // namespace SQLite
