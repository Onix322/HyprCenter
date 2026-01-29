#pragma once

#include <gtk-4.0/gtk/gtk.h>

// It's role is to manage the app
class App {

private:
  GtkApplication *_app;
  GtkBuilder *_buidler;
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

  void set_app(GtkApplication *app);

  void set_builder(GtkBuilder *builder);

  GtkBuilder *get_builder();

  GtkApplication *get_app();

  bool isRunning();
};
