#pragma once

#include "YTEngine/Core/Defines.h"

#include <filesystem>

namespace Yor
{
  namespace FS = std::filesystem;

  class Path
  {
  public:
    Path() = default;
    Path(const char* path);
    Path(const std::string& path);

    std::string readToString() const;

    bool exists() const;
    bool isFile() const;

    std::string toString() const { return m_path.string(); }

  private:
    FS::path m_path;
  };
}