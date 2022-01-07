#pragma once

namespace SQLite {
    namespace Impl_ {
        struct Data final {

            int cols_;
            char** keys_;
            char** values_;

            Data(const int cols, char** const values, char** const keys) noexcept;

            Data(const Data& lval) = delete;
            Data& operator=(const Data& lval) = delete;

            Data(Data&& rval) noexcept;
            Data& operator=(Data&& rval) noexcept;

            ~Data();
        };
    } // namespace Impl_
} // namespace SQLite
