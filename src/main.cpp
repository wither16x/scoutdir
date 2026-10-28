#include "bruteforce.h"
#include "cli.h"
#include "curl_context.h"
#include "wordlist.h"
#include <exception>
#include <memory>
#include <print>
#include <stdexcept>

int main(int argc, char *argv[])
{
    try {
        CURLContext curl;
        std::unique_ptr<Wordlist> wordlist;

        title();
        check_arg_count(argc);

        for (int i = 1; i < argc; i++) {
            if (is_argument(argv[i], k_arg_help)) {
                help();
            } else if (is_argument(argv[i], k_arg_wordlist)) {
                if (not argv[i + 1])
                    throw std::runtime_error("missing wordlist");

                wordlist = std::make_unique<Wordlist>(argv[i + 1]);

                std::println("Wordlist: {}", wordlist->path());
                std::println("Total words: {}\n", wordlist->word_count());
            } else if (is_argument(argv[i], k_arg_url)) {
                if (not argv[i + 1])
                    throw std::runtime_error("missing URL");

                bruteforce(curl, *wordlist, argv[i + 1]);
            }
        }
        return EXIT_SUCCESS;
    } catch (const std::exception &e) {
        std::println(stderr, "\033[1;31mERROR\033[0m: {}.", e.what());
        return EXIT_FAILURE;
    }
}