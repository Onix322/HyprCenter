#!/bin/bash

if [[ "$1" != "-fl" ]]; then
  echo "Standard build mode (Disabling ASan)..."
  # Explicitly set sanitize to none
  meson setup build --reconfigure -Db_sanitize=none || meson setup build -Db_sanitize=none
  meson compile -C build && ./build/src/hyprcenter
else
  echo "Memory Debug mode (ASan) enabled..."
  meson setup build --reconfigure -Db_sanitize=address -Db_lundef=false || \
    meson setup build -Db_sanitize=address -Db_lundef=false

  if meson compile -C build; then
    export ASAN_OPTIONS="detect_leaks=1"
    export LSAN_OPTIONS="report_indirect_leaks=0:suppressions=$(pwd)/lsan.supp"    
    ./build/src/hyprcenter
  else
    exit 1
  fi
fi
