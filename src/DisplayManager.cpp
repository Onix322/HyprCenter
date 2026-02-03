#include "App.hpp"
#include "UserInterface.hpp"
#include "glib-object.h"
#include "gtk/gtk.h"
#include <DisplayManager.hpp>
#include <stdexcept>

std::mutex DisplayManager::mtx;
DisplayManager *DisplayManager::instance_ptr = nullptr;

void DisplayManager::init(App *application,
                          UserInterfaceProvider *ui_provicer) {
  std::lock_guard<std::mutex> lock(mtx);
  if (instance_ptr == nullptr) {
    instance_ptr = new DisplayManager(application, ui_provicer);
  }
}

DisplayManager *DisplayManager::get_instance() {
  if (instance_ptr == nullptr) {
    throw new std::runtime_error(
        "No instance initialized. Use DisplayManager.init() first and then "
        "call get_instance");
  }
  return instance_ptr;
}

void DisplayManager::show_ui(UserInterface *ui) {

  UserInterface *ui_found = this->_ui_provider->get_ui_by_name(ui->get_name());

  GtkBuilder *builder = _application->get_builder();
  // do something with ui_found
  GObject *app_container_obj =
      gtk_builder_get_object(builder, "display-container");
  GObject *container_content = gtk_builder_get_object(builder, "content");

  gtk_box_remove(GTK_BOX(app_container_obj), GTK_WIDGET(container_content));
  gtk_box_append(GTK_BOX(app_container_obj), ui_found->get_content());

  this->_current_ui = ui_found;
}

UserInterface *DisplayManager::get_current_ui() { return nullptr; }
