#pragma once

#include "../sqlite/DataBase.hpp"

namespace Passman {
    struct CredentialsSource final {

        CredentialsSource(const std::string_view dbpath) noexcept;

      private:
        SQLite::DataBase db_;
    };
} // namespace Passman
