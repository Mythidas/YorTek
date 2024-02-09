#pragma once

#include "YTEngine/Core/Window.h"
#include "YTEngine/Graphics/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Yor::Windows
{
  class W_Window : public Window
  {
  public:
    W_Window(const Builder& builder);
    ~W_Window();

    virtual void onUpdate() override;

    virtual std::string getTitle() const override { return m_builder.title; }
    virtual uint32_t getWidth() const override { return m_builder.width; }
    virtual uint32_t getHeight() const override { return m_builder.height; }
    virtual void* getNativeWindow() const override { return m_window; }

    virtual void setTitle(const std::string& title) override;
    virtual void setCursorMode(bool locked) override;

  private:
    Builder m_builder;
    GLFWwindow* m_window;
    Unique<GraphicsContext> m_graphicsContext;
  };
}