#pragma once

#include "YTEngine/Graphics/RenderCommands.h"

namespace Yor::OGL
{
  class OGL_RenderCommands : public RenderCommands
  {
  public:
    OGL_RenderCommands() = default;

  protected:
    virtual void _enableDepthTesting(bool enable) override;
    virtual void _setClearColor(float r, float g, float b) override;
    virtual void _resize(int width, int height) override;
  };
}