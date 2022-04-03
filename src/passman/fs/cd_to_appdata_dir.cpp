#include "cd_to_appdata_dir.hpp"

#include <filesystem>

#include "../../util/ExitCode.hpp"
#include "../../util/fcheck.hpp"
#include "../err_msg.hpp"

void Passman::FS::cd_to_appdata_dir(const std::string_view appdata_sv) noexcept
{
    std::error_code errc;

    std::filesystem::current_path(appdata_sv, errc);
    fcheck(!errc, [lappdata_sv = appdata_sv] {
        err_msg("Cannot change directory to :", std::quoted(lappdata_sv)._M_string, " (is appdata), exiting");
        std::exit(exit_failure);
    });
}
