#include "curl_context.h"
#include "http.h"
#include "wordlist.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <exception>
#include <memory>
#include <print>
#include <stdexcept>
#include <string>
#include <utility>
#include <curl/curl.h>

int main(int argc, char *argv[])
{
    try {
        CURLContext curl;
        std::unique_ptr<Wordlist> wordlist;

        std::println("                            __      .___.__        \n"
    "  ______ ____  ____  __ ___/  |_  __| _/|__|______ \n"
    " /  ___// ___\\/  _ \\|  |  \\   __\\/ __ | |  \\_  __ \\\n"
    " \\___ \\  \\__(  <_> )  |  /|  | / /_/ | |  ||  | \\/\n"
    "/____  >\\___  >____/|____/ |__| \\____ | |__||__|   \n"
    "     \\/     \\/                       \\/            ");
        std::println("=====================================================\n"
        "Free and open-source directory bruteforcer.\n");

        if (argc <= 1) {
            std::println("Maybe try with an option? Use -h to list them all.");
            return EXIT_SUCCESS;
        }

        for (int i = 1; i < argc; i++) {
            if (std::strcmp(argv[i], "-h") == 0) {
                std::println("Available options:\n"
                "-h                             show this message\n"
                "-w <pathname>                  set the wordlist\n"
                "-u <url>                       start URL"
                );
            } else if (std::strcmp(argv[i], "-w") == 0) {
                wordlist = std::make_unique<Wordlist>(argv[i + 1]);

                std::println("Wordlist: {}", wordlist->path());
                std::println("Total words: {}\n", wordlist->word_count());
            } else if (std::strcmp(argv[i], "-u") == 0) {
                if (wordlist->empty())
                    throw std::runtime_error("it looks like no wordlist has been provided."
                    "Try again with -w <pathname>.");

                for (auto &word : wordlist->words()) {
                    std::string new_url = argv[i + 1];
                    new_url += word;

                    HTTPResponseCode response = curl.request(new_url);
                    if (response != HTTPResponseCode::PageNotFound)
                        std::println("\33[2K\r\033[1;32mFOUND\033[0m: {} ({})", new_url, std::to_underlying(response));
                    else
                        std::print("\33[2K\r\033[0;90mNOT FOUND: {} ({})\033[0m", new_url, 404);
                    std::fflush(stdout);
                }
            }
        }
        return EXIT_SUCCESS;
    } catch (const std::exception &e) {
        std::println(stderr, "\033[1;31mERROR\033[0m: {}.", e.what());
        return EXIT_FAILURE;
    }
}