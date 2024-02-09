#include "YTEngine/Core/Window.h"
#include "Platform/Windows/W_Window.h"

namespace Yor
{
  Unique<Window> Window::Builder::build() const
  {
    return CreateUnique<Windows::W_Window>(*this);
  }
}