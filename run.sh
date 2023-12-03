#!/usr/bin/env bash

cmake -S . -B build && rm -rv build/assets && cp -r assets build && pushd build; make && ./raylib_game; popd
