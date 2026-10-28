#include "cli.h"
#include <print>
#include <stdexcept>

void help()
{
    std::println("Available options:\n"
        "{}                             show this message\n"
        "{} <pathname>                  set the wordlist\n"
        "{} <url>                       start URL",
        k_arg_help, k_arg_wordlist, k_arg_url
    );
}

void title()
{
    std::println("                            __      .___.__        \n"
                 "  ______ ____  ____  __ ___/  |_  __| _/|__|______ \n"
                 " /  ___// ___\\/  _ \\|  |  \\   __\\/ __ | |  \\_  __ \\\n"
                 " \\___ \\  \\__(  <_> )  |  /|  | / /_/ | |  ||  | \\/\n"
                 "/____  >\\___  >____/|____/ |__| \\____ | |__||__|   \n"
                 "     \\/     \\/                       \\/            ");
    std::println("=====================================================\n"
    "Free and open-source directory bruteforcer.\n");
}

void check_arg_count(int argc)
{
    if (argc <= 1)
        throw std::runtime_error("maybe try with an option? Use -h to list them all");
}