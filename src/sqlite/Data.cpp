#include "Data.hpp"

#include <cstdlib>
#include <cstring>
#include <utility>

using namespace SQLite::Impl_;

static int inclusive_strlen(const char* str) {
    return strlen(str) + 1;
}

Data& Data::operator=(Data&& rval) noexcept {
    std::swap(rval.keys_, keys_);
    std::swap(rval.values_, values_);

    this->cols_ = rval.cols_;

    return *this;
}
Data::Data(Data&& rval) noexcept
    : cols_{rval.cols_}, keys_{std::exchange(rval.keys_, nullptr)}, values_{
                                                                        std::exchange(rval.values_,
                                                                                      nullptr)} {
}
Data::Data(const int cols, char** const values, char** const keys) noexcept : cols_{cols} {

    keys_ = new char*[cols];

    for (int i = 0; i < cols; i++) {

        const int len = inclusive_strlen(keys[i]);
        keys_[i] = new char[len];

        for (int j = 0; j < len; j++) {
            keys_[i][j] = keys[i][j];
        }
    }

    values_ = new char*[cols];

    for (int i = 0; i < cols; i++) {

        if (values[i] == nullptr) {
            values_[i] = nullptr;
            continue;
        }

        const int len = inclusive_strlen(values[i]);
        values_[i] = new char[len];

        for (int j = 0; j < len; j++) {
            values_[i][j] = values[i][j];
        }
    }
}

Data::~Data() {
    // note : SIGSEGV if indexing nullptr[0] => *(nullptr + 0)

    if (keys_ != nullptr) {
        for (int i = 0; i < cols_; i++) {
            delete[] keys_[i];
        }
    }

    if (values_ != nullptr) {
        for (int i = 0; i < cols_; i++) {
            delete[] values_[i];
        }
    }

    delete[] keys_;
    delete[] values_;
}

