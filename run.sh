#!/usr/bin/env bash

rm -r holdout/assets;
cmake -S . -B holdout && cp -r assets holdout && pushd holdout; make && ./holdout; popd
rm -fr holdout/CMakeFiles holdout/cmake_install.cmake holdout/CMakeCache.txt holdout/Makefile;