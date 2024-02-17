#pragma once

#include "YTEngine/Reflection/Object.h"

namespace Yor
{
  class Color : public Object
  {
  public:
    float r = 0;
    float g = 0;
    float b = 0;

    virtual void _registerData() override
    {
      _registerProperty<float>("R", offsetof(Color, r));
      _registerProperty<float>("G", offsetof(Color, g));
      _registerProperty<float>("B", offsetof(Color, b));
    }
  };
  OBJ_CLASS(Color)
}