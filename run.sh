#!/usr/bin/env bash

cmake -S . -B build && pushd build; make && ./raylib_game; popd
