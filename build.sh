#!/usr/bin/env bash

set -eu

to_build=${1?"Pass a cc file to build"}

g++ \
    -Wall -Wextra -pedantic \
    -std=c++14 \
    -I third_party/libosmium/include/ \
    -I third_party/sol/ \
    $to_build -pthread -lz \
    -I /usr/include/lua5.2 -llua5.2 \
