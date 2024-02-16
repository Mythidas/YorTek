#include "YTEngine/Scripting/ScriptLoader.h"
#include "YTEngine/Tools/Path.h"
#include "YTEngine/Debug/Log.h"
#include "YTEngine/Reflection/ApplicationDomain.h"

namespace Yor
{
  std::vector<DLLSource> ScriptLoader::s_engineDlls;

  void ScriptLoader::_loadEngineModules()
  {
    auto dllPaths = Path("C:\\Programming\\Desktop\\YorTek\\bin\\Debug-windows-x86_64\\Editor").getFilesInDir(FileExtensionFilters::DLL);
    for (auto& path : dllPaths)
    {
      DLLSource src(path);
      if (src.load())
      {
        src.call("ImportComponents", &ApplicationDomain::get());
        s_engineDlls.push_back(src);
      }
    }
  }

  void ScriptLoader::_freeEngineModules()
  {
    for (auto& dll : s_engineDlls)
      dll.free();

    s_engineDlls.clear();
  }
}