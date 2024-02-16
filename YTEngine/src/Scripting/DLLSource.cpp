#include "YTEngine/Scripting/DLLSource.h"

#include <Windows.h>

namespace Yor
{
  DLLSource::DLLSource(const Path& path)
    : m_srcPath(path)
  {
  }

  bool DLLSource::load()
  {
    m_dllSrc = LoadLibrary(m_srcPath.toWString().c_str());
    return m_dllSrc;
  }

  // TODO: create a way to call functions that return variables and take variables
  void DLLSource::call(const char* func)
  {
    if (!m_dllSrc) return;

    FuncPtr funcPtr = (FuncPtr)GetProcAddress((HMODULE)m_dllSrc, func);
    if (funcPtr)
      funcPtr();
  }

  void DLLSource::free()
  {
    if (!m_dllSrc) return;

    FreeLibrary((HMODULE)m_dllSrc);
  }
  void* DLLSource::_getProcAddress(const char* func)
  {
    return GetProcAddress((HMODULE)m_dllSrc, func);
  }
}