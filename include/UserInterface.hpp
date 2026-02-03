#pragma once
#include <gtk/gtk.h>
#include <string>
class UserInterface {

private:
  std::string name;
  std::string button_name;
  GtkWidget *content;
  GtkCallbackAction *callback; // functionality

  UserInterface();

public:
  UserInterface(std::string name, std::string button_name, GtkWidget *content,
                GtkCallbackAction *callback) {
    this->name = name;
    this->button_name = button_name;
    this->content = content;
    this->callback = callback;
  };

  std::string get_name() { return name; };
  std::string get_button_name() { return button_name; }
  GtkWidget *get_content() { return content; };
  GtkCallbackAction *get_callbak() { return callback; };
};
