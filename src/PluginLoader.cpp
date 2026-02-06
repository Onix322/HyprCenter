
#include "PluginLoader.hpp"
#include "UserInterfaceProvider.hpp"
#include <dlfcn.h>
#include <filesystem>
#include <iostream>
#include <mutex>

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

void PluginLoader::load_plugin(fs::path path) {
  std::cout << "Loading plugin: " << path.lexically_normal().string()
            << std::endl;

  void *handle = dlopen(path.c_str(), RTLD_LAZY);

  if (!handle) {
    std::cerr << "Cannot open library: " << dlerror() << '\n';
    return;
  }

  // load the symbol
  std::cout << "Loading symbol hello...\n";
  typedef void (*hyprcenter_plugin_init_t)();

  // reset errors
  dlerror();
  hyprcenter_plugin_init_t hpi =
      (hyprcenter_plugin_init_t)dlsym(handle, "hyprcenter_plugin_init");
  const char *dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "Cannot load symbol 'hyprcenter_plugin_init': " << dlsym_error
              << '\n';
    dlclose(handle);
    return;
  }

  // use it to do the calculation
  std::cout << "Calling method...\n";
  hpi();

  // close the library
  std::cout << "Closing library...\n";
  dlclose(handle);

  std::cout << "Plugin loaded!!!!";
}

void PluginLoader::load_plugins() {}
