#include "UserInterfaceProvider.hpp"
#include "UserInterface.hpp"

std::mutex UserInterfaceProvider::mtx;
UserInterfaceProvider *UserInterfaceProvider::instance_ptr = nullptr;

UserInterfaceProvider *UserInterfaceProvider::get_instance() {
  std::lock_guard<std::mutex> lock_thread(mtx);
  if (instance_ptr == nullptr) {
    instance_ptr = new UserInterfaceProvider();
  }
  return instance_ptr;
}

void UserInterfaceProvider::register_ui(UserInterface *ui) {
  _user_interface_container.insert_or_assign(ui->get_name(), ui);
};

UserInterface *UserInterfaceProvider::get_ui_by_name(std::string ui_name) {
  return _user_interface_container[ui_name];
};

std::map<std::string, UserInterface *> UserInterfaceProvider::get_all_ui() {
  return this->_user_interface_container;
}
