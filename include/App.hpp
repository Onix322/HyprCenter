#pragma once

#include "DisplayManager.hpp"
#include "UserInterfaceProvider.hpp"
#include <gtk-4.0/gtk/gtk.h>

// It's role is to manage the app
class App {

private:
  GtkApplication *_gtk_app;
  UserInterfaceProvider *_ui_provider;
  DisplayManager *_display_manager;
  bool _running;

  bool verify_window() { return _gtk_app != NULL; }

  static App *_instance;
  static std::mutex mtx;

  App(DisplayManager *display_manager, UserInterfaceProvider *ui_provider) {
    _display_manager = display_manager;
    _ui_provider = ui_provider;
  };

public:
  // move
  App(App &&) = delete;
  // copy
  App(const App &) = delete;
  App &operator=(App &&) = delete;
  App &operator=(const App &) = delete;
  ~App() = default;

  static void init(DisplayManager *display_manager,
                   UserInterfaceProvider *ui_provider);

  static App *get_instance();

  void start();

  void stop();

  DisplayManager *get_display_manager();

  UserInterfaceProvider *get_ui_provider();

  bool isRunning();
};
