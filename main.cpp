#include "include/App.hpp"
#include <gtk-4.0/gtk/gtk.h>
#include <hyprlang.hpp>

int main() {
  App *app = new App();

  app->start();

  return 0;
}
