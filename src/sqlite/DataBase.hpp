#pragma once

extern "C" {
#include <sqlite3.h>
}

#include <concepts>
#include <string_view>
#include <vector>

#include "error/Code.hpp"
#include "impl/DataBaseContext.hpp"
#include "impl/Data_tag.hpp"

namespace SQLite::Impl_ {
    template <typename DataT>
    int sql_select_callback(void* voidptr,
                            const int cols,
                            char** const values,
                            char** const keys) noexcept
    {
        reinterpret_cast<std::vector<DataT>*>(voidptr)->emplace_back(values, keys);
        return SQLite::Error::Code::OK;
    }
} // namespace SQLite::Impl_

namespace SQLite {
    struct DataBase final {

        DataBase(const std::string_view dbpath) noexcept;

        Error::Code execute(const std::string_view sql_request) noexcept;

        template <typename DataT, std::size_t ReserveV = sizeof(DataT) <= 1024 ? 100 : 8>
        requires std::is_base_of_v<Impl_::Data_tag, DataT>
        auto select(const std::string_view sql_select_request) noexcept
        {
            std::vector<DataT> ret;
            ret.reserve(ReserveV);

            const auto c_api_ret = sqlite3_exec(ctx_.ptr(),
                                                sql_select_request.data(),
                                                Impl_::sql_select_callback<DataT>,
                                                &ret,
                                                nullptr);

            return std::pair<std::vector<DataT>, SQLite::Error::Code>{
                ret,
                static_cast<Error::Code>(c_api_ret)};
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

