#include "YTEngine/Debug/Debug.h"

#include <iostream>

namespace Yor
{
  void Debug::log(const char* msg)
  {
    std::cout << "File: " << __FILE__ << msg << std::endl;
  }

  void Debug::logWarn(const char* msg)
  {
    std::cout << "File: " << __FILE__ << "Warn: " << msg << std::endl;
  }

  void Debug::logError(const char* msg)
  {
    std::cout << "File: " << __FILE__ << "Error: " << msg << std::endl;
  }

  void Debug::logCritical(const char* msg)
  {
    std::cout << "File: " << __FILE__ << "Critical: " << msg << std::endl;
  }
}