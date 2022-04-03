#pragma once

#include <string_view>
#include <tuple>
#include <vector>

#include "../sqlite/DataBase.hpp"

namespace Passman {
    struct CredentialsSource final {

        CredentialsSource(const std::string_view dbpath) noexcept;

        std::vector<std::tuple<std::string, std::string, unsigned long, unsigned long>> get() noexcept;
        std::tuple<std::string, unsigned long, unsigned long> get(const std::string_view login) noexcept;

        void add(const std::string_view login, const std::string_view password) noexcept;
        void add(const std::string_view login) noexcept;

      private:
        SQLite::DataBase db_;
    };
} // namespace Passman
