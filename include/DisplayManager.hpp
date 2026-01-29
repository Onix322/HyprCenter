#pragma once

#include "App.hpp"
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

  App *_application;
  UserInterface *_current_ui;
  UserInterfaceProvider *_ui_provider;

  DisplayManager(App *application, UserInterfaceProvider *ui_provider) {
    _application = application;
    _ui_provider = ui_provider;
  };

public:
  DisplayManager(DisplayManager &&) = delete;
  DisplayManager &operator=(const DisplayManager &) = delete;
  ~DisplayManager() = default;

  static void init(App *application, UserInterfaceProvider *ui_provicer);

  static DisplayManager *get_instance();

  // it will show / change the ui displayed in "display-container"
  void show_ui(UserInterface *ui);

  UserInterface *get_current_ui();
};
