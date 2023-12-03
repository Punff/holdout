#!/usr/bin/env bash

cmake -S . -B build && cp -r assets build && pushd build; make && ./raylib_game; popd
