#include "UserInterface.hpp"
#include "glib-object.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"
#include <UserInterfaceProvider.hpp>
#include <iostream>

GtkCallbackAction *ui_functionality() { return nullptr; }

GtkWidget *get_widget_from_file() {
  GtkBuilder *builder = gtk_builder_new_from_file("./System.ui");

  GObject *content_widget = gtk_builder_get_object(builder, "content");

  return GTK_WIDGET(content_widget);
}

extern "C" UserInterface *
hyprcenter_plugin_init(UserInterfaceProvider *ui_provider) {

  UserInterface *system_ui =
      new UserInterface("system_information", "System Informations",
                        get_widget_from_file(), ui_functionality());

  (std::cout << "DEBUG !!!!!! ") << std::endl;

  return system_ui;
};
