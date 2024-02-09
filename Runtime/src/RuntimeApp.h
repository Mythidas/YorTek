#pragma once

#include <YTEngine.h>

namespace Runtime
{
  class RuntimeApp : public Yor::Application
  {
  public:
    RuntimeApp();

    virtual void onStart() override;
    virtual void onUpdate() override;
  };
}