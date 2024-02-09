#include "RuntimeApp.h"

int main()
{
  Runtime::RuntimeApp* app = new Runtime::RuntimeApp();

  app->Run();
  delete app;
  return 0;
}