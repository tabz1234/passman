#pragma once

#include <string_view>

namespace Passman::FS {
    void touch_appdata_dir(const std::string_view appdata_sv) noexcept;
}
