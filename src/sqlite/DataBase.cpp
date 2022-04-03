#include "DataBase.hpp"

using namespace SQLite;

DataBase::DataBase(const std::string_view dbpath) noexcept : ctx_{dbpath}
{
}

Error::Code DataBase::execute(const std::string_view sql_request) noexcept
{
    const auto c_api_ret = sqlite3_exec(ctx_.ptr(), sql_request.data(), nullptr, nullptr, nullptr);

    return static_cast<Error::Code>(c_api_ret);
}
