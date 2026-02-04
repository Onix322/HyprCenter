// ROLE:
// This will scan a folder for .so plugins
#include <filesystem>
#include <mutex>
#include <vector>

namespace fs = std::filesystem;

class PluginScanner {
private:
  PluginScanner();
  static std::mutex mtx;
  static PluginScanner *instance;

public:
  static PluginScanner *get_instance() {
    if (nullptr == instance) {
      std::lock_guard<std::mutex> lock(mtx);
      instance = new PluginScanner();
      return instance;
    }
    return instance;
  }

  // returns a string with paths found in directory
  std::vector<std::filesystem::path> scan_dir(fs::path &dir_path);
};
