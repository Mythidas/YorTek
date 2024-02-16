#pragma once

#include "YTEngine/Scripting/DLLSource.h"

namespace Yor
{
  class ScriptLoader
  {
  public:


  private:
    friend class Application;

    static void _loadEngineModules();
    static void _freeEngineModules();

    static std::vector<DLLSource> s_engineDlls;
  };
}