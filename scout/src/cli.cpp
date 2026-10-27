#include "scout/cli.h"
#include <stdexcept>

void check_argument_count(int argc)
{
    if (argc < kMinOptionCount)
        throw std::runtime_error("No option given. Use --help for a list of options.");
}