#pragma once

#include <YTEngine.h>
#include <YTEngine/Physics/Rigidbody.h>

namespace Yor::Scripts
{
  class YT_API NativeComponent
  {
  public:
    Physics::Rigidbody rb;
    int importCount;
  };
}