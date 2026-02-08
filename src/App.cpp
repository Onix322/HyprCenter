#include "DisplayManager.hpp"
#include "PluginLoader.hpp"
#include "PluginScanner.hpp"
#include "UserInterface.hpp"
#include "UserInterfaceProvider.hpp"
#include "gio/gio.h"
#include "glib-object.h"
#include "glib.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"
#include <App.hpp>
#include <vector>

App::App() : _app(nullptr), _running(false) {}

// used to send more data to 'handle_display_ui' func
struct DisplayUiDetailsToHandle {
  DisplayManager *display_manager;
  GtkBuilder *app_builder;
};

DisplayUiDetailsToHandle *details = new DisplayUiDetailsToHandle();

void handle_display_ui(GtkButton *button, gpointer user_data) {

  UserInterface *ui = (UserInterface *)user_data;
  details->display_manager->show_ui(details->app_builder, ui);
}

void init_plugins(UserInterfaceProvider *ui_provider) {

  PluginScanner *scanner = PluginScanner::get_instance();
  PluginLoader::init(ui_provider);
  PluginLoader *loader = PluginLoader::get_instance();

  fs::path location("./libs");
  std::vector<fs::path> paths = scanner->scan_dir(location);
  loader->load_plugin_array(paths);
}

void init_app_ui(GtkApplication *gtk_app, gpointer app_pointer) {

  // CREATING APP UI
  GtkBuilder *builder = gtk_builder_new_from_file("resources/HyprCenter.ui");
  App *app = static_cast<App *>(app_pointer);

  details->display_manager = app->get_display_manager();
  details->app_builder = builder;

  // REGISTERING BUTTONS AND UI
  // ui
  init_plugins(app->get_ui_provider());
  // buttons
  GtkBox *options_container =
      GTK_BOX(gtk_builder_get_object(builder, "options_container"));

  auto all_ui = app->get_ui_provider()->get_all_ui();

  for (auto ui_entry : all_ui) {

    GtkWidget *button =
        gtk_button_new_with_label(ui_entry.second->get_button_name().c_str());
    gtk_box_append(options_container, button);

    g_signal_connect(button, "clicked", G_CALLBACK(handle_display_ui),
                     ui_entry.second);
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
  delete details;
  details = nullptr;
  this->_running = false;
}

DisplayManager *App::get_display_manager() { return this->_display_manager; }

bool App::isRunning() { return this->_running; }

UserInterfaceProvider *App::get_ui_provider() { return this->_ui_provider; }
