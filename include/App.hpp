#pragma once

#include "DisplayManager.hpp"
#include "UserInterfaceProvider.hpp"
#include <gtk-4.0/gtk/gtk.h>

// It's role is to manage the app
class App {

private:
  GtkApplication *_app;
  UserInterfaceProvider *_ui_provider;
  DisplayManager *_display_manager;
  bool _running;

  bool verify_window() { return _app != NULL; }
  App();

public:
  App(DisplayManager *display_manager, UserInterfaceProvider *ui_provider) {
    _display_manager = display_manager;
    _ui_provider = ui_provider;
  };

  // move
  App(App &&) = delete;
  // copy
  App(const App &) = delete;
  App &operator=(App &&) = delete;
  App &operator=(const App &) = delete;
  ~App() = default;

  void start();

  void stop();

  DisplayManager *get_display_manager();

  UserInterfaceProvider *get_ui_provider();

  bool isRunning();
};
