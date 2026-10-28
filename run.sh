#!/bin/bash

set -euo pipefail

# change compiler if needed
clang++ -std=c++23 scoutdir.cpp -o scoutdir -lcurl

./scoutdir "$@"