#include <PluginScanner.hpp>
#include <filesystem>
#include <unistd.h>
#include <vector>

namespace fs = std::filesystem;
PluginScanner *PluginScanner::instance = nullptr;
std::mutex PluginScanner::mtx;
PluginScanner::PluginScanner() {}

PluginScanner *PluginScanner::get_instance() {
  if (nullptr == instance) {
    std::lock_guard<std::mutex> lock(mtx);
    instance = new PluginScanner();
    return instance;
  }
  return instance;
}
std::vector<std::filesystem::path> PluginScanner::scan_dir(fs::path &dir_path) {

  std::vector<std::filesystem::path> paths;

  for (auto dir_entry : fs::recursive_directory_iterator(dir_path)) {
    if (!dir_entry.is_directory()) {
      paths.push_back(dir_entry.path());
    }
  }
  return paths;
}
