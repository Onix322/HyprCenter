#include "UserInterfaceProvider.hpp"
#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"
#include <App.hpp>

App::App() : _app(nullptr), _running(false) {}

void init_app_ui(GtkApplication *gtk_app, gpointer app_pointer) {

  // GATHERING DATA
  GtkBuilder *builder = gtk_builder_new_from_file("resources/HyprCenter.ui");
  App *app = static_cast<App *>(app_pointer);
  app->set_builder(builder);

  // registering buttons and ui
  GtkBox *options_container =
      GTK_BOX(gtk_builder_get_object(builder, "options_container"));

  auto all_ui = app->get_ui_provider()->get_all_ui();

  for (auto ui_entry : all_ui) {

    GtkWidget *button =
        gtk_button_new_with_label(ui_entry.second->get_button_name().c_str());
    gtk_box_append(options_container, button);
  }

  // GETTING WINDOW
  GtkApplicationWindow *app_window = GTK_APPLICATION_WINDOW(
      gtk_builder_get_object(builder, "application-window"));

  gtk_window_set_application(GTK_WINDOW(app_window), gtk_app);

  // DRAW
  gtk_window_present(GTK_WINDOW(app_window));
}

// first method called
void App::start() {
  this->_app =
      gtk_application_new("io.github.hyprcenter", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(_app, "activate", G_CALLBACK(init_app_ui), this);

  int status = g_application_run(G_APPLICATION(_app), 0, nullptr);

  this->_running = status == 0;
}

void App::stop() {
  g_application_quit(G_APPLICATION(_app));
  this->_running = false;
}

void App::set_builder(GtkBuilder *builder) { this->_buidler = builder; }

void App::set_app(GtkApplication *app) { this->_app = app; }

GtkApplication *App::get_app() { return this->_app; }

GtkBuilder *App::get_builder() { return _buidler; }

bool App::isRunning() { return this->_running; }

UserInterfaceProvider *App::get_ui_provider() { return this->_ui_provider; }
