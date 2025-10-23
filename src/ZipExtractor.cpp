#include "ZipExtractor.hpp"

#include <cstring>
#include <filesystem>
#include <zip_file.hpp>

void ZipExtractor::extract(const std::string& what, const std::string& where)
{
    miniz_cpp::zip_file zip(what);

    for (const miniz_cpp::zip_info& zip_info : zip.infolist())
    {
        std::filesystem::path filePath = std::filesystem::path(where) / zip_info.filename;
        std::filesystem::path parentDirectory = filePath.parent_path();

        if (!std::filesystem::exists(parentDirectory))
            std::filesystem::create_directories(parentDirectory);

        if (!std::filesystem::is_directory(filePath))
        {
            std::ofstream outFile(filePath, std::ios::binary);
            outFile << zip.read(zip_info.filename);
        }
    }
}