#include "RuntimeApp.h"

#include <iostream>

namespace Runtime
{
  RuntimeApp::RuntimeApp()
    : Application({ Yor::ApplicationBackend::OpenGL })
  {
  }

  void RuntimeApp::onStart()
  {
  }

  void RuntimeApp::onUpdate()
  {
    if (Yor::Input::IsKeyPressed(Yor::KeyCode::A))
    {
      std::cout << "A" << std::endl;
    }
  }
}