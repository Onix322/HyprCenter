#pragma once
#include <gtk/gtk.h>
#include <string>
class UserInterface {

private:
  std::string name;
  GtkWidget *layout;
  GtkCallbackAction *callback; // functionality

  UserInterface();

public:
  UserInterface(std::string, GtkLayoutChild *layout,
                GtkCallbackAction *callback);

  std::string get_name() { return name; };
  GtkWidget *get_widget() { return layout; };
  GtkCallbackAction *get_callbak() { return callback; };
};
