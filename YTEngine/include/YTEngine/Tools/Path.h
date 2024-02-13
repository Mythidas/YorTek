#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Tools/Flags.h"

#include <filesystem>

namespace Yor
{
  namespace FS = std::filesystem;

  enum class FileDialogFilters
  {
    Project,
    Scene,
    Text,
    JPG,
    PNG
  };

  YT_FLAG_OPERATORS(FileDialogFilters)

  class Path
  {
  public:
    Path() = default;
    Path(const char* path);
    Path(const std::string& path);
    Path(const FS::path& path);

    std::string readToString() const;
    void write(const std::string& str) const;

    bool exists() const;
    bool isFile() const;
    std::string name() const { return m_path.filename().string(); }

    std::string toString() const { return m_path.string(); }

  public:
    Path operator+(const Path& rhs) const
    {
      return m_path.string() + rhs.toString();
    }

  public:
    static Path getDirectoryDialogBox();
    static Path getFileOpenDialogBox(const FileDialogFilters& filters);
    static Path getFileSaveDialogBox(const FileDialogFilters& filters);

  private:
    FS::path m_path;
  };
}