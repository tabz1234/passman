#include "touch_appdata_dir.hpp"

#include <filesystem>

#include "../../util/ExitCode.hpp"
#include "../../util/fcheck.hpp"
#include "../err_msg.hpp"

void Passman::FS::touch_appdata_dir(const std::string_view appdata_sv) noexcept
{
    if (!std::filesystem::exists(appdata_sv)) [[unlikely]] {
        std::error_code errc;

        std::filesystem::create_directories(appdata_sv, errc);
        fcheck(!errc, [appdata_sv] {
            err_msg("Cannot create directory :", std::quoted(appdata_sv)._M_string, " (for appdata), exiting...");
            std::exit(exit_failure);
        });
    }
}
