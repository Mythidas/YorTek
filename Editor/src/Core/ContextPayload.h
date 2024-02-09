#pragma once

#include <YTEngine/Tools/Stringf.h>

namespace Yor::Editor
{
  struct ContextPayload
  {
    uint64_t targetID;
    void* data{ nullptr };
    size_t size{ 0 };

    ContextPayload(uint64_t hashId, const void* data, size_t size)
    {
      targetID = hashId;
      if (size > 0)
      {
        this->data = new char[size];
        memcpy(this->data, data, size);
      }
    }

    ~ContextPayload()
    {
      delete data;
    }

    bool isTarget(uint64_t hashId)
    {
      return targetID == hashId;
    }
  };
}