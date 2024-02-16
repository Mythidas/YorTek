#pragma once

#include <YTEngine/Core/Defines.h>
#include <YTEngine/Reflection/ApplicationDomain.h>

namespace Yor::Internal
{
  extern "C"
  {
    YT_API void ImportComponents(ApplicationDomain* domain);
  }
}