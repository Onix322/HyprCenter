#pragma once
#include <UserInterface.hpp>
#include <map>
#include <mutex>
#include <string>

//  Role:
//  ui regsitration
//  ui provider
//  Provides methods for registering and retriving an ui
class UserInterfaceProvider {

private:
  static std::mutex mtx;
  static UserInterfaceProvider *instance_ptr;

  std::map<std::string, UserInterface *> _user_interface_container;

  UserInterfaceProvider() {
    _user_interface_container = std::map<std::string, UserInterface *>();
  }

public:
  static UserInterfaceProvider *get_instance();

  void register_ui(UserInterface *ui);

  UserInterface *get_ui_by_name(std::string ui_name);

  std::map<std::string, UserInterface *> get_all_ui();
};
