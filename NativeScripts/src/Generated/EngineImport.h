#pragma once

#include <YTEngine/Reflection/ApplicationDomain.h>
#include <YTEngine/Reflection/ComponentFactory.h>

namespace Yor::Import
{
  extern "C"
  {
    void YT_API ImportComponents(ApplicationDomain* domain);
  }
}