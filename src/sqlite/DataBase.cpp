#include "DataBase.hpp"

extern "C" {
#include "sqlite3.h"
}

#include <cstdio>

#include "../ConstexprDebug.hpp"
#include "../DebugMsg.hpp"

using namespace SQLite;
using namespace SQLite::Impl_;

static int sql_callback(void* voidptr, int cols, char** values, char** keys) {

    reinterpret_cast<std::forward_list<Data>*>(voidptr)->emplace_front(cols, values, keys);
    return SQLITE_OK;
}
static int sql_callback_dumb(void* voidptr, int cols, char** values, char** keys) {
    return SQLITE_OK;
}

DataBase::DataBase(const std::string_view dbpath) : ctx_{dbpath} {
}
int DataBase::execute(const std::string_view sql_request) noexcept {

    const auto c_api_ret =
        sqlite3_exec(ctx_.ptr(), sql_request.data(), sql_callback_dumb, nullptr, nullptr);

    debugMsg(c_api_ret == SQLITE_OK, sqlite3_errstr(c_api_ret));

    return c_api_ret;
}

std::optional<std::forward_list<Data>> DataBase::requestData(const std::string_view sql_request) {

    std::forward_list<Impl_::Data> ret;

    const auto c_api_ret =
        sqlite3_exec(ctx_.ptr(), sql_request.data(), sql_callback, &ret, nullptr);

    if (c_api_ret != SQLITE_OK) {
        if constexpr (DEBUG) {
            printf("[%s]-> %s\n", __PRETTY_FUNCTION__, sqlite3_errstr(c_api_ret));
        }
        return {};
    }

    return ret;
}
