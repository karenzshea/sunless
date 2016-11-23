#!/usr/bin/env bash

g++ \
    -Wall -Wextra -pedantic \
    -std=c++14 \
    -I third_party/libosmium/include/ \
    -I third_party/sol/ \
    -I /usr/include/lua5.2 \
    main.cc -pthread -lz
