#include "get_home_path.hpp"

#include <cstdlib>

#include "../../util/fcheck.hpp"
#include "../err_msg.hpp"

std::string_view Passman::FS::get_home_path() noexcept
{
    const auto getenv_ret = getenv("HOME");
    fcheck(getenv_ret != nullptr, [] {
        err_msg("Envoirment variable \"HOME\" is not set");
    });

    return getenv_ret; // getenv ret is ptr to argp, which have libc-global lifetime
}
