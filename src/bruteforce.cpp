#include "bruteforce.h"
#include <stdexcept>
#include <print>
#include <utility>

void bruteforce(CURLContext &curl, const Wordlist &wordlist, const std::string &url)
{
    if (wordlist.empty())
        throw std::runtime_error("it looks like no wordlist has been provided."
        "Try again with -w <pathname>.");

    for (auto &word : wordlist.words()) {
        std::string new_url = url;
        new_url += word;

        HTTPResponseCode response = curl.request(new_url);
        if (response != HTTPResponseCode::PageNotFound)
            std::println("\33[2K\r\033[1;32mFOUND\033[0m: {} ({})", new_url,
                std::to_underlying(response));
        else
            std::print("\33[2K\r\033[0;90mNOT FOUND [404]: {}\033[0m", new_url);
        std::fflush(stdout);
    }
}