#include "UserInterfaceProvider.hpp"
#include "UserInterface.hpp"

std::mutex UserInterfaceProvider::mtx;
UserInterfaceProvider *UserInterfaceProvider::instance_ptr = nullptr;

void UserInterfaceProvider::register_ui(UserInterface *ui) {
  _user_interface_container.insert_or_assign(ui->get_name(), ui);
};

UserInterface *UserInterfaceProvider::get_ui_by_name(std::string ui_name) {
  return _user_interface_container[ui_name];
};

std::map<std::string, UserInterface *> UserInterfaceProvider::get_all_ui() {
  return this->_user_interface_container;
}
