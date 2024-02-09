#include "YTEngine/Tools/Path.h"

#include <fstream>

namespace Yor
{
  Path::Path(const char* path)
    : m_path(path)
  {
  }

  Path::Path(const std::string& path)
    : m_path(path)
  {
  }

  std::string Path::readToString() const
  {
    if (!exists() || !isFile()) return std::string();

    std::ifstream stream(m_path.c_str());
    if (!stream.is_open()) return std::string();

    std::stringstream buf;
    buf << stream.rdbuf();
    stream.close();
    return buf.str();
  }

  bool Path::exists() const
  {
    return FS::exists(m_path);
  }

  bool Path::isFile() const
  {
    return !FS::is_directory(m_path);
  }
}