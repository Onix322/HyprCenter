#pragma once

#include <UserInterface.hpp>
#include <UserInterfaceProvider.hpp>

#include <mutex>
// Its' role is to display / draw the ui
// Role:
// display ui
class DisplayManager {

private:
  static DisplayManager *instance_ptr;
  static std::mutex mtx;

  UserInterface *_current_ui;

  DisplayManager() {};

public:
  DisplayManager(const DisplayManager &) = delete;
  DisplayManager &operator=(const DisplayManager &) = delete;
  DisplayManager(DisplayManager &&) = delete;
  DisplayManager &operator=(DisplayManager &&) = delete;
  ~DisplayManager() = default;

  static DisplayManager *get_instance();

  // it will show / change the ui displayed in "display-container"
  void show_ui(GtkBuilder *builder, UserInterface *ui);

  UserInterface *get_current_ui();
};
