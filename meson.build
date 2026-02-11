project(
  'hyprcenter',
  'cpp',
  'c',
  version: '0.1.0',
  default_options: ['cpp_std=c++23'],
)

gtk_dep = dependency('gtk4')
adwaita_dep = dependency('libadwaita-1')
hyprlang_dep = dependency('hyprlang')

inc = 'include'

sources = files(
  'src/App.cpp',
  'src/DisplayManager.cpp',
  'src/PluginLoader.cpp',
  'src/PluginScanner.cpp',
  'src/UserInterfaceProvider.cpp',
)

subdir('src')
subdir('tests')
