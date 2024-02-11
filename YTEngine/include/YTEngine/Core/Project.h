#pragma once

#include "YTEngine/Tools/Path.h"

namespace Yor
{
  class Project
  {
  public:
    static void newProject();
    static void loadProject();
    static void saveProject();

    static const Path& getProjectPath() { return s_projectPath; }

  private:
    // Editable project info
    static inline Path s_projectPath;

    // Internal
    static inline bool s_projectLoaded;
  };
}