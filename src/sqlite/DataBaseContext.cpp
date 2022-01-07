#include "DataBaseContext.hpp"

extern "C" {
#include "sqlite3.h"
}

#include "../check.hpp"

using namespace SQLite::Impl_;

DataBaseContext::DataBaseContext(const std::string_view dbpath) {

    const auto c_api_ret = sqlite3_open(dbpath.data(), &raw_ctx_);
    check(c_api_ret == SQLITE_OK, "sqlite3_open failed");
}

sqlite3* DataBaseContext::ptr() noexcept {
    return raw_ctx_;
}
DataBaseContext::~DataBaseContext() {
    sqlite3_close(raw_ctx_);
}

