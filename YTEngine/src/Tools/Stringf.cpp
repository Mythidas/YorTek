#include "YTEngine/Tools/Stringf.h"

namespace Yor
{
  std::unordered_map<std::string, uint64_t> Stringf::s_hashedStrings;

  uint64_t Stringf::hash(const std::string& data)
  {
    if (s_hashedStrings.contains(data)) return s_hashedStrings[data];

    uint64_t h = hash(data.c_str());
    s_hashedStrings[data] = h;

    return h;
  }
}