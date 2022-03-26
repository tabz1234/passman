#include "to_str.hpp"

extern "C" {
#include <sqlite3.h>
}

std::string SQLite::Error::to_str(const Code errc) noexcept
{
    return sqlite3_errstr(errc);
}
