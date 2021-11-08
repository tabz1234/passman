#ifndef READFILE_HPP
#define READFILE_HPP

#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

static std::vector<char>
readFile(const std::filesystem::path& path_to_file)
{
    std::ifstream infile(path_to_file, std::ios::binary);

    size_t file_size = std::filesystem::file_size(path_to_file);
    std::vector<char> vec(file_size);

    infile.read(vec.data(), file_size);

    return vec;
}

#endif
