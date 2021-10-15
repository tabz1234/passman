#ifndef CREATEFILE_HPP
#define CREATEFILE_HPP

#include <filesystem>
#include <fstream>

#include <iostream>

static void
createFile(const std::filesystem::path& filepath) noexcept
{
    const auto dir = std::filesystem::directory_entry(filepath.parent_path());
    std::filesystem::create_directories(dir);
    std::ofstream(dir.path() / filepath.filename().c_str(), std::ios::out);
}

#endif
