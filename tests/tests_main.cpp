#include "PluginLoader.hpp"
#include "UserInterfaceProvider.hpp"
#include <PluginScanner.hpp>
#include <filesystem>
#include <iostream>
#include <vector>

// UTILITY
#define LOG_RESULT(boolean, test_name)                                         \
  {                                                                            \
    if (boolean) {                                                             \
      std::cout << "TEST PASSED: " << test_name << std::endl;                  \
    } else {                                                                   \
      std::cout << "TEST FAILED: " << test_name << std::endl;                  \
    }                                                                          \
  }

template <typename T> bool equality_arrays(T arr1, T arr2) {

  int arr1_len = (long)sizeof(*arr1) / sizeof(arr1[0]);

  int arr2_len = (long)sizeof(*arr2) / sizeof(arr2[0]);

  if (arr1_len != arr2_len)
    return false;

  for (long i = 0; i < arr1_len; i++) {
    if (arr1[i] != arr2[i])
      return false;
  }
  return true;
}

// TESTS
void test_PluginScanner_scan_dir_func(PluginScanner *instance) {

  // PREP
  std::filesystem::path path("./tests/test_plugins_scanner");

  // EXPECTED
  std::filesystem::path expected[2] = {
      std::filesystem::path("./tests/test_plugins_scanner/testlib.so"),
      std::filesystem::path("./tests/test_plugins_scanner/testlib2.so"),
  };

  // OUTPUT
  std::vector<std::filesystem::path> plugins_paths = instance->scan_dir(path);

  LOG_RESULT(equality_arrays(expected, plugins_paths.data()),
             "TEST PluginScanner->scan_dir");
}

void test_PluginLoader_load_one_plugin(PluginLoader *instance) {
  // PREP

  std::filesystem::path path =
      std::filesystem::path(std::getenv("HOME")) /
      "Documents/projects/hyprcenter/libs/system-info-ui/build" /
      "libhyprcenter-system-info-ext.so";

  // EXPECTED
  // bool result = true;

  // OUTPUT
  instance->load_plugin(path.lexically_normal());
}

// TESTING AREA
int main() {

  std::cout << "!!!!!!!!! TESTING AREA !!!!!!!!!" << std::endl;

  // INIT AREA
  PluginScanner *plugin_scanner_instance = PluginScanner::get_instance();

  UserInterfaceProvider *ui_provider = UserInterfaceProvider::get_instance();

  PluginLoader::init(ui_provider);
  PluginLoader *plugin_loader_instance = PluginLoader::get_instance();
  //
  // TEST AREA
  test_PluginScanner_scan_dir_func(plugin_scanner_instance);
  test_PluginLoader_load_one_plugin(plugin_loader_instance);

  return 0;
}
