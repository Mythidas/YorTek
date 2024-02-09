#pragma once

#include <unordered_map>
#include <string>

namespace Yor
{
  class Stringf
  {
  public:
    static uint64_t hash(const std::string& data);

    // Murmur64bit
    static constexpr uint64_t hash(const char* str)
    {
      uint64_t hash(525201411107845655ull);
      for (; *str; ++str)
      {
        hash ^= *str;
        hash *= 0x5bd1e9955bd1e995;
        hash ^= hash >> 47;
      }
      return hash;
    }

  private:
    static std::unordered_map<std::string, uint64_t> s_hashedStrings;
  };
}

constexpr uint64_t operator""_hs(const char* str, std::size_t len)
{
  return Yor::Stringf::hash(str);
}