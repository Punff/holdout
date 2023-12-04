#!/usr/bin/env bash

rm -r build/assets;
cmake -S . -B build && cp -r assets build && pushd build; make && ./raylib_game; popd
