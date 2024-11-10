#!/bin/sh
set -e

find src include \( -name "*.c" -or -name "*.cpp" -or -name "*.h" -or -name "*.hpp" \) -exec clang-format-17 -i --verbose {} +
