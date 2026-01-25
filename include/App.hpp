#pragma once

#include <gtk-4.0/gtk/gtk.h>

class App {

private:
  GtkApplication *_app;
  bool _running;

  bool verify_window() { return _app != NULL; }

public:
  App();
  App(App &&) = default;
  App(const App &) = default;
  App &operator=(App &&) = default;
  App &operator=(const App &) = default;
  ~App() = default;

  void start();

  void stop();

  bool isRunning();
};
