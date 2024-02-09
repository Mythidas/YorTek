#pragma once

namespace Yor
{
  class Debug
  {
  public:
    static void log(const char* msg);
    static void logWarn(const char* msg);
    static void logError(const char* msg);
    static void logCritical(const char* msg);
  };
}