#pragma once

#include <string_view>

struct sqlite3;

namespace SQLite::Impl_ {
    struct DataBaseContext final { // unique_ptr is not the case here

        DataBaseContext(const std::string_view dbpath) noexcept;

        sqlite3* ptr() noexcept;
        const sqlite3* ptr() const noexcept;

        ~DataBaseContext();

      private:
        sqlite3* raw_ctx_;

      public:
        DataBaseContext(const DataBaseContext&) noexcept = delete;
        DataBaseContext& operator=(const DataBaseContext&) noexcept = delete;

        DataBaseContext(DataBaseContext&&) noexcept = delete;
        DataBaseContext& operator=(DataBaseContext&&) noexcept = delete;
    };
} // namespace SQLite::Impl_

