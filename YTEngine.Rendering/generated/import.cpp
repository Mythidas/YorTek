#include "import.h"

#include "YTEngine/Rendering/SpriteRenderer.h"

#include <YTEngine/Reflection/ComponentFactory.h>

namespace Yor::Internal
{
  void ImportComponents(ApplicationDomain* domain)
  {
    auto spriteRenderer = ComponentFactory<SpriteRenderer>()
      .data<&SpriteRenderer::color>("Color", offsetof(SpriteRenderer, color))
      .build(domain);
  }
}