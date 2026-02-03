#include <PluginScanner.hpp>
#include <iostream>

void test_PluginScanner_scan_dir_func(PluginScanner *instance) {

  std::cout << "TESTING PluginScanner->scan_dir()" << std::endl;
}

int main() {

  std::cout << "!!!!!!!!! TESTING AREA !!!!!!!!!!" << std::endl;

  // INIT AREA
  PluginScanner *plugin_scanner_instance = PluginScanner::get_instance();
  //
  // TEST AREA
  test_PluginScanner_scan_dir_func(plugin_scanner_instance);

  return 0;
}
