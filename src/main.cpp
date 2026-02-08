#include "DisplayManager.hpp"
#include <App.hpp>
#include <UserInterfaceProvider.hpp>
#include <gtk-4.0/gtk/gtk.h>
#include <hyprlang.hpp>
App *app = nullptr;

void close_app() {
  if (!app->isRunning()) {
    app->stop();
    delete app;
    app = nullptr;
  }
}

void handle_interuption(int sig) {
  close_app();
  exit(sig);
}

int main() {

  DisplayManager *display_manager = DisplayManager::get_instance();
  UserInterfaceProvider *ui_provider = UserInterfaceProvider::get_instance();

  app = new App(display_manager, ui_provider);

  signal(SIGINT, handle_interuption);
  signal(SIGTERM, handle_interuption);

  app->start();
  // after gtk loop close
  close_app();
  return 0;
}
