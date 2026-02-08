#include "PluginLoader.hpp"
#include "UserInterface.hpp"
#include "UserInterfaceProvider.hpp"
#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <mutex>
#include <vector>

namespace fs = std::filesystem;

PluginLoader *PluginLoader::_instance = nullptr;
std::mutex PluginLoader::mtx;

void PluginLoader::init(UserInterfaceProvider *ui_provider) {
  std::lock_guard<std::mutex> lock_thread(mtx);
  if (_instance == nullptr) {
    _instance = new PluginLoader(ui_provider);
  }
}

PluginLoader *PluginLoader::get_instance() { return _instance; }

bool PluginLoader::load_plugin(fs::path path) {
  std::cout << "Loading plugin: " << path.lexically_normal().string()
            << std::endl;

  void *handle = dlopen(path.c_str(), RTLD_LAZY);

  if (!handle) {
    std::cerr << "Cannot open library: " << dlerror() << std::endl;
    return false;
  }

  // load the symbol
  typedef UserInterface *(*hyprcenter_plugin_init_t)();

  // reset errors
  dlerror();
  hyprcenter_plugin_init_t hyprcenter_plugin_init =
      (hyprcenter_plugin_init_t)dlsym(handle, "hyprcenter_plugin_init");
  const char *dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "Cannot load symbol 'hyprcenter_plugin_init': " << dlsym_error
              << std::endl;
    dlclose(handle);
    return false;
  }

  // use it to do the calculation
  this->_ui_provider->register_ui(hyprcenter_plugin_init());

  // close the library
  dlclose(handle);

  std::cout << "Plugin loaded!!!!" << std::endl;

  return true;
}

bool PluginLoader::load_plugin_array(std::vector<fs::path> &paths) {
  for (fs::path file_path : paths) {
    if (fs::is_directory(file_path) ||
        file_path.extension().compare(".so") != 0) {
      std::cerr << "Not a .so file";
      return false;
    }

    bool state = load_plugin(file_path);
    if (!state)
      return false;
  }
  return true;
}
