#include "include/App.hpp"
#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include "gtk/gtk.h"

App::App() : _app(nullptr), _running(false) {}

void activate_helper(GtkApplication *app, gpointer windowptr) {

  GtkApplicationWindow *app_window =
      GTK_APPLICATION_WINDOW(gtk_application_window_new(app));

  GtkLabel *label = GTK_LABEL(gtk_label_new("HELLO WORLD"));

  gtk_window_set_child(GTK_WINDOW(app_window), GTK_WIDGET(label));

  gtk_window_present(GTK_WINDOW(app_window));
}

void App::start() {

  _app =
      gtk_application_new("io.github.hyprcenter", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(_app, "activate", G_CALLBACK(activate_helper), _app);

  g_application_run(G_APPLICATION(_app), 0, nullptr);
}

void App::stop() {
  _running = false;
  g_application_quit(G_APPLICATION(_app));
}

bool App::isRunning() { return _running; }
