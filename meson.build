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

sources = files(
  'src/App.cpp',
  'src/DisplayManager.cpp',
  'main.cpp',
)

executable(
  'hyprcenter',
  sources,
  dependencies: [gtk_dep, adwaita_dep, hyprlang_dep],
  include_directories: 'include',
  install: true,
)
