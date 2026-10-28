#include <cstring>
#include <fstream>
#include <print>
#include <stdlib.h>
#include <string>
#include <vector>
#include <curl/curl.h>

int main(int argc, char *argv[])
{
    CURL *curl_handle;
    CURLcode curl_res;
    long http_code;
    std::vector<std::string> wordlist;

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

    curl_handle = curl_easy_init();
    if (not curl_handle) {
        std::println(stderr, "\033[1;31mERROR\033[0m: Could not initialize CURL handle.");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "-h") == 0) {
            std::println("Available options:\n"
            "-h                             show this message\n"
            "-w <pathname>                  set the wordlist\n"
            "-u <url>                       start URL"
            );
        } else if (std::strcmp(argv[i], "-w") == 0) {
            std::ifstream file(argv[i + 1]);
            std::string ln;

            while (file >> ln)
                wordlist.push_back(ln);

            std::println("Wordlist: {}", argv[i + 1]);
            std::println("Total words: {}\n", wordlist.size());
        } else if (std::strcmp(argv[i], "-u") == 0) {
            if (wordlist.empty()) {
                std::println(stderr, "\033[1;31mERROR\033[0m: It looks like no wordlist has been provided."
                "Try again with -w <pathname>.");
                return EXIT_FAILURE;
            }

            curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "HEAD");
            curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

            for (auto &word : wordlist) {
                std::string new_url = argv[i + 1];
                new_url += word;
                curl_easy_setopt(curl_handle, CURLOPT_URL, new_url.c_str());

                curl_res = curl_easy_perform(curl_handle);
                if (curl_res != CURLE_OK) {
                    std::println(stderr, "\033[1;31mERROR\033[0m: {}", curl_easy_strerror(curl_res));
                    return EXIT_FAILURE;
                }

                curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

                if (http_code != 404)
                    std::println("\33[2K\r\033[1;32mFOUND\033[0m: {} ({})", new_url.c_str(), http_code);
                else
                    std::print("\33[2K\r\033[0;90mNOT FOUND: {} ({})\033[0m", new_url, 404);
                std::fflush(stdout);
            }
        }
    }

    curl_easy_cleanup(curl_handle);

    return EXIT_SUCCESS;
}