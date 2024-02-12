#pragma once

#include <YTEngine/Math/Vector3.h>

#include <string>

namespace Yor::Editor
{
  class Controls
  {
  public:
    static void DrawVector3(const std::string& label, Vector3& vec3);
  };
}