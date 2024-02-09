#include "YTEngine/Core/UUID.h"

#include <random>

namespace Yor
{
  UUID::UUID()
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dist(0, INVALID - 1);
    m_uuid = dist(gen);
  }

  UUID::UUID(uint64_t uuid)
    : m_uuid(uuid)
  {
  }

  bool UUID::valid() const
  {
      return m_uuid != INVALID;
  }

  uint64_t UUID::uint() const
  {
    return m_uuid;
  }
}