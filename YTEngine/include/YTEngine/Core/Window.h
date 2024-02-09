#pragma once

#include "YTEngine/Core/Defines.h"
#include "YTEngine/Core/Event.h"

#include <string>

namespace Yor
{
  enum class WindowState
  {
    Windowed,
    Minimized,
    Fullscreen
  };

  class Window
  {
  public:
    Event<> OnWindowClose; // No arguments
    Event<int, int> OnWindowResize; // Width, Height
    Event<int> OnKeyPressed; // Key
    Event<int> OnKeyReleased; // Key
    Event<double, double> OnMouseMoved; // Mouse X, Mouse Y
    Event<float> OnMouseScrolled; // Direction
    Event<int> OnMouseButtonPressed; // Button
    Event<int> OnMouseButtonReleased; // Button

    struct Builder
    {
      std::string title{ "AxtonEngine" };
      uint32_t width{ 1280 };
      uint32_t height{ 720 };
      bool fixedAspectRatio{ true };
      bool vSync{ false };

      Builder& setTitle(const std::string& title) { this->title = title; return *this; }
      Builder& setWidth(const uint32_t width) { this->width = width; return *this; }
      Builder& setHeight(const uint32_t height) { this->height = height; return *this; }
      Builder& setFixedAspectRatio(const bool aspr) { this->fixedAspectRatio = aspr; return *this; }
      Builder& setVSync(const bool vsync) { this->vSync = vsync; return *this; }
      Unique<Window> build() const;
    };

    virtual void onUpdate() = 0;

    virtual std::string getTitle() const = 0;
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;
    virtual void* getNativeWindow() const = 0;

    virtual void setTitle(const std::string& title) = 0;
    virtual void setCursorMode(bool locked) = 0;
  };
}