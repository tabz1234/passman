#include "DataBaseContext.hpp"

extern "C" {
#include "sqlite3.h"
}

using namespace SQLite::Impl_;

DataBaseContext::DataBaseContext(const std::string_view dbpath) noexcept
{
    sqlite3_open(dbpath.data(), &raw_ctx_);
}

sqlite3* DataBaseContext::ptr() noexcept
{
    return raw_ctx_;
}
const sqlite3* DataBaseContext::ptr() const noexcept
{
    return raw_ctx_;
}
DataBaseContext::~DataBaseContext()
{
    sqlite3_close(raw_ctx_);
}

