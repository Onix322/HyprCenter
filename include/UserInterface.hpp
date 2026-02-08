#pragma once
#include <gtk/gtk.h>
#include <string>
class UserInterface {

private:
  std::string name;
  std::string button_name;
  GtkWidget *content;

  UserInterface();

public:
  UserInterface(std::string name, std::string button_name, GtkWidget *content) {
    this->name = name;
    this->button_name = button_name;
    this->content = content;
  };

  std::string get_name() { return name; };
  std::string get_button_name() { return button_name; }
  GtkWidget *get_content() { return content; };
};
