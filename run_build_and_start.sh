#!/bin/bash
meson setup build --reconfigure && meson compile -C build && ./build/src/hyprcenter
