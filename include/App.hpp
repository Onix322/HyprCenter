#pragma once

#include "UserInterfaceProvider.hpp"
#include <gtk-4.0/gtk/gtk.h>

// It's role is to manage the app
class App {

private:
  GtkApplication *_app;
  GtkBuilder *_buidler;
  UserInterfaceProvider *_ui_provider;
  bool _running;

  bool verify_window() { return _app != NULL; }
  App();

public:
  App(UserInterfaceProvider *ui_provider) { _ui_provider = ui_provider; };

  // move
  App(App &&) = delete;
  // copy
  App(const App &) = delete;
  App &operator=(App &&) = delete;
  App &operator=(const App &) = delete;
  ~App() = default;

  void start();

  void stop();

  void set_app(GtkApplication *app);

  void set_builder(GtkBuilder *builder);

  GtkBuilder *get_builder();

  GtkApplication *get_app();

  UserInterfaceProvider *get_ui_provider();

  bool isRunning();
};
