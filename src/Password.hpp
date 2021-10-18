#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include "PasswordInfo.hpp"

struct Password
{
    std::string str_;
    PasswordInfo info_;

    Password(const PasswordInfo& info) noexcept;
};

#endif
