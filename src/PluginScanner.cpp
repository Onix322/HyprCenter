#include <PluginScanner.hpp>
#include <filesystem>
#include <unistd.h>
#include <vector>

namespace fs = std::filesystem;
PluginScanner *PluginScanner::instance = nullptr;
std::mutex PluginScanner::mtx;
PluginScanner::PluginScanner() {}
std::vector<std::string> PluginScanner::scan_dir(fs::path &dir_path) {

  std::vector<std::string> paths;

  for (auto dir_entry : fs::recursive_directory_iterator(dir_path)) {
    if (!dir_entry.is_directory()) {
      paths.push_back(dir_entry.path().string());
    }
  }
  return paths;
}
