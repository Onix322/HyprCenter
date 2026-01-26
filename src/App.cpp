#include "include/App.hpp"
#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"

App::App() : _app(nullptr), _running(false) {}

void draw_window(GtkApplication *app, gpointer builder_ptr) {

  GtkBuilder *builder = gtk_builder_new_from_file("resources/HyprCenter.ui");

  // GETTING WINDOW
  GtkApplicationWindow *app_window = GTK_APPLICATION_WINDOW(
      gtk_builder_get_object(builder, "application-window"));

  gtk_window_set_application(GTK_WINDOW(app_window), app);
  gtk_window_present(GTK_WINDOW(app_window));
}

void App::start() {

  this->_app =
      gtk_application_new("io.github.hyprcenter", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(_app, "activate", G_CALLBACK(draw_window), NULL);

  int status = g_application_run(G_APPLICATION(_app), 0, nullptr);

  this->_running = status == 0;
}

void App::stop() {
  g_application_quit(G_APPLICATION(_app));
  this->_running = false;
}

void App::set_app(GtkApplication *app) { this->_app = app; }

GtkApplication *App::get_app() { return this->_app; }

bool App::isRunning() { return this->_running; }
