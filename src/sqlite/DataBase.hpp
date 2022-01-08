#pragma once

#include <forward_list>
#include <optional>
#include <string_view>

#include "DataBaseContext.hpp"
#include "ErrCode.hpp"

namespace SQLite {
    struct DataBase final {

        explicit DataBase(const std::string_view dbpath);

        std::optional<ErrCode> execute(const std::string_view sql_request) noexcept;

        std::optional<std::forward_list<Impl_::Data>>
        requestData(const std::string_view sql_request);

      private:
        Impl_::DataBaseContext ctx_;

      public:
        DataBase(const DataBase&) = delete;
        DataBase& operator=(const DataBase&) = delete;

        DataBase(DataBase&&) noexcept = delete;
        DataBase& operator=(DataBase&&) noexcept = delete;
    };
} // namespace SQLite
