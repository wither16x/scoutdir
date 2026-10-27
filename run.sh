#!/bin/bash

set -euo pipefail

# change compiler if needed
gcc scout.c -o scout

./scout "$@"