#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Tools/Flags.h"

#include <filesystem>

namespace Yor
{
  namespace FS = std::filesystem;

  enum class FileExtensionFilters
  {
    Any,
    Project,
    Scene,
    Text,
    JPG,
    PNG,
    DLL
  };

  YT_FLAG_OPERATORS(FileExtensionFilters)

  class Path
  {
  public:
    Path() = default;
    Path(const char* path);
    Path(const std::string& path);
    Path(const FS::path& path);

    std::string readToString() const;
    void write(const std::string& str) const;
    std::vector<Path> getFilesInDir(const FileExtensionFilters& filter);

    bool exists() const;
    bool isFile() const;
    std::string extension() const { return m_path.extension().string(); }
    std::string name() const { return m_path.filename().string(); }

    std::string toString() const { return m_path.string(); }
    std::wstring toWString() const { return m_path.wstring(); }

  public:
    Path operator+(const Path& rhs) const
    {
      return m_path.string() + rhs.toString();
    }

  public:
    static Path getCurrentDir();
    static Path getDirectoryDialogBox();
    static Path getFileOpenDialogBox(const FileExtensionFilters& filters);
    static Path getFileSaveDialogBox(const FileExtensionFilters& filters);

  private:
    FS::path m_path;
  };
}