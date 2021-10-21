#include "sqlite_return.hpp"

#include <cstring>
#include <stdlib.h>
#include <utility>

static int
inclusive_strlen(const char* str) noexcept
{
    return strlen(str) + 1;
}

sqlite_return::sqlite_return(const int rc) noexcept
  : rc_{ rc }
{}
sqlite_return::sqlite_return(const sqlite_return& lval) noexcept
  : sqlite_return(lval.rows_count_, lval.ppvalues_, lval.ppkeys_)
{}

sqlite_return&
sqlite_return::operator=(const sqlite_return& lval) noexcept
{
    return *this =
             sqlite_return(lval.rows_count_, lval.ppvalues_, lval.ppkeys_);
}

sqlite_return&
sqlite_return::operator=(sqlite_return&& rval) noexcept
{
    std::swap(rval.ppkeys_, ppkeys_);
    std::swap(rval.ppvalues_, ppvalues_);

    this->rc_ = rval.rc_;
    this->rows_count_ = rval.rows_count_;

    return *this;
}
sqlite_return::sqlite_return(sqlite_return&& rval) noexcept
  : rows_count_{ rval.rows_count_ }
  , rc_{ rval.rc_ }
  , ppkeys_{ std::exchange(rval.ppkeys_, nullptr) }
  , ppvalues_{ std::exchange(rval.ppvalues_, nullptr) }
{}
sqlite_return::sqlite_return(int rows_count,
                             char** ppvalues,
                             char** ppkeys) noexcept
  : rows_count_{ rows_count }
{

    ppkeys_ = new char*[rows_count_];

    for (int i = 0; i < rows_count_; i++) {

        const int len = inclusive_strlen(ppkeys[i]);
        ppkeys_[i] = new char[len];

        for (int j = 0; j < len; j++) {
            ppkeys_[i][j] = ppkeys[i][j];
        }
    }

    ppvalues_ = new char*[rows_count_];
    for (int i = 0; i < rows_count_; i++) {

        if (ppvalues[i] == nullptr) {
            ppvalues_[i] = nullptr;
            continue;
        }

        const int len = inclusive_strlen(ppvalues[i]);
        ppvalues_[i] = new char[len];

        for (int j = 0; j < len; j++) {
            ppvalues_[i][j] = ppvalues[i][j];
        }
    }
}

sqlite_return::~sqlite_return()
{
    for (int i = 0; i < rows_count_; i++) {
        delete[] ppkeys_[i];
        delete[] ppvalues_[i];
    }
    delete[] ppkeys_;
    delete[] ppvalues_;
}

