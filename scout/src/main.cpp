#include "scout/cli.h"
#include <cstdlib>
#include <exception>
#include <print>

int main(int argc, char *argv[])
{
    try {
        std::println("scout -- The free directory bruteforcer");

        check_argument_count(argc);
    } catch (const std::exception &e) {
        std::println("ERROR: {}", e.what());
    }

    return EXIT_SUCCESS;
}