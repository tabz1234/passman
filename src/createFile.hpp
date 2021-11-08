#ifndef CREATEFILE_HPP
#define CREATEFILE_HPP

#include <filesystem>
#include <fstream>

static void
createFile(const std::filesystem::path& filepath)
{
    std::filesystem::create_directories(filepath.parent_path());
    std::ofstream(filepath.c_str(), std::ios::out);
}

#endif
