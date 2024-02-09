#pragma once

#include "YTEngine/Core/Defines.h"

namespace Yor
{
  class ImGUIDisplay
  {
  public:
    struct Builder
    {
      Unique<ImGUIDisplay> build() const;
    };

  public:
    virtual void beginUI() = 0;
    virtual void endUI() = 0;

  public:
    static void useDarknessTheme();
  };
}