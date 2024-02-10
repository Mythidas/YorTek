#pragma once

#include <unordered_map>
#include <string>

namespace Yor::Editor
{
  using MenuPath = std::unordered_map<std::string, std::vector<std::string>>;

  class EditorMainMenu
  {
  public:
    void onGUI();

  private:
    void _drawWindowMenu();
    void _drawWindowMenuItem(const MenuPath& menuPath, const std::string& str, const std::vector<std::string>& items);
  };
}