#!/usr/bin/env bash

BUILD_FLAGS=-j8
CAN_RUN_TESTS=true

if [[ $# -ne 0 ]]; then
  BUILD_FLAGS=$@
  CAN_RUN_TESTS=false
fi

mkdir -p build
cd build
cmake -Wno-dev -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -- $BUILD_FLAGS

if [[ $? -ne 0 ]]; then
  exit $?
fi

if [[ $CAN_RUN_TESTS == true ]]; then
  ./bin/tests
fi
