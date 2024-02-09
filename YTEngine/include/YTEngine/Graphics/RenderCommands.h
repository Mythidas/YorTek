#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Tools/Singleton.h"

namespace Yor
{
  class RenderCommands : public Singleton<RenderCommands>
  {
  public:
    struct Builder
    {
      Unique<RenderCommands> build() const;
    };

    static void enableDepthTesting(bool enable) { get()._enableDepthTesting(enable); }
    static void setClearColor(float r, float g, float b) { get()._setClearColor(r, g, b); }
    static void resize(int width, int height) { get()._resize(width, height); }

  protected:
    virtual void _enableDepthTesting(bool enable) = 0;
    virtual void _setClearColor(float r, float g, float b) = 0;
    virtual void _resize(int width, int height) = 0;
  };
}