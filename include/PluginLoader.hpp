#pragma once
#include "UserInterfaceProvider.hpp"
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class PluginLoader {
private:
  static PluginLoader *_instance;
  static std::mutex mtx;
  UserInterfaceProvider *_ui_provider;
  PluginLoader(UserInterfaceProvider *ui_provider) {
    this->_ui_provider = ui_provider;
  };

public:
  PluginLoader(PluginLoader &&) = delete;
  PluginLoader(const PluginLoader &) = delete;
  PluginLoader &operator=(PluginLoader &&) = default;
  PluginLoader &operator=(const PluginLoader &) = default;
  ~PluginLoader() = default;

  static void init(UserInterfaceProvider *ui_provider);
  static PluginLoader *get_instance();

  bool load_plugin_array(std::vector<fs::path> &dir_path);

  bool load_plugin(fs::path path);
};
