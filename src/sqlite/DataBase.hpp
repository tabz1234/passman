#pragma once

extern "C" {
#include <sqlite3.h>
}

#include <array>
#include <concepts>
#include <string_view>
#include <vector>

#include "StaticData.hpp"
#include "error/Code.hpp"
#include "impl/DataBaseContext.hpp"
#include "impl/Data_tag.hpp"

namespace SQLite::Impl_ {
    template <int TableSZ>
    int sql_dynamic_select_static_data_callback(void* voidptr, const int cols, char** const values, char** const keys) noexcept
    {
        reinterpret_cast<std::vector<StaticData<TableSZ>>*>(voidptr)->emplace_back(values, keys);
        return SQLite::Error::Code::OK;
    }

    template <int TableSZ>
    int sql_select_one_static_data_callback(void* voidptr, const int cols, char** const values, char** const keys) noexcept
    {
        reinterpret_cast<std::optional<StaticData<TableSZ>>*>(voidptr)->emplace(values, keys);
        return SQLite::Error::Code::OK;
    }
} // namespace SQLite::Impl_

namespace SQLite {
    struct DataBase final {

        DataBase(const std::string_view dbpath) noexcept;

        Error::Code execute(const std::string_view sql_request) noexcept;

        template <template <int TableSZ> typename DataT, int TableSZ>
        requires std::is_base_of_v<Impl_::Data_tag, DataT<TableSZ>>
        auto select(const std::string_view sql_select_request, std::size_t ReserveV = sizeof(DataT<TableSZ>) <= 1024 ? 100 : 8) noexcept
        {
            std::vector<DataT<TableSZ>> ret;
            ret.reserve(ReserveV);

            const auto c_api_ret =
                sqlite3_exec(ctx_.ptr(), sql_select_request.data(), Impl_::sql_dynamic_select_static_data_callback<TableSZ>, &ret, nullptr);

            return std::pair<std::vector<DataT<TableSZ>>, SQLite::Error::Code>{ret, static_cast<Error::Code>(c_api_ret)};
        }
        template <template <int TableSZ> class DataT, int TableSZ>
        requires std::is_base_of_v<Impl_::Data_tag, DataT<TableSZ>>
        auto select_one(const std::string_view sql_select_request) noexcept
        {
            std::optional<DataT<TableSZ>> ret;

            const auto c_api_ret =
                sqlite3_exec(ctx_.ptr(), sql_select_request.data(), Impl_::sql_select_one_static_data_callback<TableSZ>, &ret, nullptr);

            return std::pair<std::optional<DataT<TableSZ>>, SQLite::Error::Code>{ret, static_cast<Error::Code>(c_api_ret)};
        }

      private:
        Impl_::DataBaseContext ctx_;

      public:
        DataBase(const DataBase&) noexcept = delete;
        DataBase& operator=(const DataBase&) noexcept = delete;

        DataBase(DataBase&&) noexcept = delete;
        DataBase& operator=(DataBase&&) noexcept = delete;
    };
} // namespace SQLite

