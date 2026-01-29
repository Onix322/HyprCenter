#pragma once
#include "include/UserInterface.hpp"
#include <map>
#include <mutex>

//  Role:
//  ui regsitration
//  ui provider
//  Provides methods for registering and retriving an ui
class UserInterfaceProvider {

private:
  static std::mutex mtx;
  static UserInterfaceProvider *instance_ptr;

  std::map<std::string, UserInterface> _user_interface_container;

  UserInterfaceProvider() {
    _user_interface_container = std::map<std::string, UserInterface>();
  }

public:
  void register_ui(UserInterface *ui) {

  };
  UserInterface *get_ui_by_name(std::string ui_name) { return nullptr; };

  static UserInterfaceProvider *get_instance() {
    std::lock_guard<std::mutex> lock_thread(mtx);
    if (instance_ptr == nullptr) {
      instance_ptr = new UserInterfaceProvider();
    }
    return instance_ptr;
  }
};
