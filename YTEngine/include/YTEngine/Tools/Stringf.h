#pragma once

#include <unordered_map>
#include <string>

namespace Yor
{
  class Stringf
  {
  public:
    static std::vector<std::string> splitBy(const std::string& str, const char delim);

    // Murmur64bit
    static uint64_t hash(const std::string& data);
    static inline constexpr uint64_t hash(const char* str);

  private:
    static std::unordered_map<std::string, uint64_t> s_hashedStrings;
  };
}

inline constexpr uint64_t Yor::Stringf::hash(const char* str)
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

constexpr uint64_t operator""_hs(const char* str, std::size_t len)
{
  return Yor::Stringf::hash(str);
}