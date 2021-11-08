#include "sqlite_return.hpp"

#include <cstring>
#include <stdlib.h>
#include <utility>

static int
inclusive_strlen(const char* str)
{
    return strlen(str) + 1;
}

sqlite_return::sqlite_return(const sqlite_return& lval)
  : sqlite_return{ lval.cols_, lval.ppvalues_, lval.ppkeys_ }
{}

sqlite_return&
sqlite_return::operator=(const sqlite_return& lval)
{
    return *this = sqlite_return{ lval.cols_, lval.ppvalues_, lval.ppkeys_ };
}

sqlite_return&
sqlite_return::operator=(sqlite_return&& rval) noexcept
{
    std::swap(rval.ppkeys_, ppkeys_);
    std::swap(rval.ppvalues_, ppvalues_);

    this->cols_ = rval.cols_;

    return *this;
}
sqlite_return::sqlite_return(sqlite_return&& rval) noexcept
  : cols_{ rval.cols_ }
  , ppkeys_{ std::exchange(rval.ppkeys_, nullptr) }
  , ppvalues_{ std::exchange(rval.ppvalues_, nullptr) }
{}
sqlite_return::sqlite_return(int cols_, char** ppvalues, char** ppkeys)
  : cols_{ cols_ }
{

    ppkeys_ = new char*[cols_];

    for (int i = 0; i < cols_; i++) {

        const int len = inclusive_strlen(ppkeys[i]);
        ppkeys_[i] = new char[len];

        for (int j = 0; j < len; j++) {
            ppkeys_[i][j] = ppkeys[i][j];
        }
    }

    ppvalues_ = new char*[cols_];
    for (int i = 0; i < cols_; i++) {

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
    // note : SIGSEGV if indexing nullptr[0] => *(nullptr + 0)

    for (int i = 0; i < cols_ && ppkeys_ != nullptr; i++) {
        delete[] ppkeys_[i];
    }

    for (int i = 0; i < cols_ && ppvalues_ != nullptr; i++) {
        delete[] ppvalues_[i];
    }

    delete[] ppkeys_;
    delete[] ppvalues_;
}

