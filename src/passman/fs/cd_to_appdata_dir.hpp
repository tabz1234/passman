#pragma once

#include <string_view>

namespace Passman::FS {
    void cd_to_appdata_dir(const std::string_view appdata_sv) noexcept;
} // namespace Passman::FS
