#include "UserInterface.hpp"
#include "gtk/gtk.h"
#include <DisplayManager.hpp>

std::mutex DisplayManager::mtx;
DisplayManager *DisplayManager::instance_ptr = nullptr;

DisplayManager *DisplayManager::get_instance() {
  std::lock_guard<std::mutex> lock(mtx);
  if (instance_ptr == nullptr) {
    instance_ptr = new DisplayManager();
  }
  return instance_ptr;
}

void DisplayManager::show_ui(GtkBuilder *builder, UserInterface *ui) {
  if (this->_current_ui == ui)
    return;

  GtkStack *app_container_obj =
      GTK_STACK(gtk_builder_get_object(builder, "display-container"));

  if (gtk_widget_get_parent(ui->get_content()) == nullptr) {
    gtk_stack_add_named(app_container_obj, GTK_WIDGET(ui->get_content()),
                        ui->get_name().c_str());
  }

  gtk_stack_set_visible_child(app_container_obj, ui->get_content());

  this->_current_ui = ui;
}

UserInterface *DisplayManager::get_current_ui() { return _current_ui; }
