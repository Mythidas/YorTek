#pragma once

#include "YTEngine/Tools/Path.h"

namespace Yor
{
  class DLLSource
  {
    typedef void (*FuncPtr)();
  public:
    DLLSource() = default;
    DLLSource(const Path& path);

    bool load();
    void call(const char* func);
    void free();
    
    template <typename... Args>
    void call(const char* func, Args... args);

  private:
    void* _getProcAddress(const char* func);

  private:
    Path m_srcPath;
    void* m_dllSrc;
  };

  template<typename ...Args>
  inline void DLLSource::call(const char* func, Args ...args)
  {
    if (!m_dllSrc) return;
    typedef void (*FncPtrArgs)(Args...);

    FncPtrArgs funcPtr = (FncPtrArgs)_getProcAddress(func);
    if (funcPtr)
      funcPtr(args...);
  }
}