#!/bin/bash

set -euo pipefail

# change compiler if needed
gcc scoutdir.c -o scoutdir -lcurl

./scoutdir "$@"