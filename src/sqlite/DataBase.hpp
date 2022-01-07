#pragma once

#include <forward_list>
#include <optional>
#include <string_view>

#include "DataBaseContext.hpp"

namespace SQLite {
    struct DataBase final {

        explicit DataBase(const std::string_view dbpath);

        int execute(const std::string_view sql_request) noexcept;

        std::optional<std::forward_list<Impl_::Data>>
        requestData(const std::string_view sql_request);

      private:
        Impl_::DataBaseContext ctx_;

      public:
    };
} // namespace SQLite
