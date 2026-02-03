#include <App.hpp>
#include <UserInterfaceProvider.hpp>
#include <gtk-4.0/gtk/gtk.h>
#include <hyprlang.hpp>

int main() {

  UserInterfaceProvider *ui_provider = UserInterfaceProvider::get_instance();

  App *app = new App(ui_provider);

  app->start();

  if (!app->isRunning()) {
    delete app;
    delete ui_provider;
  }
  return 0;
}
