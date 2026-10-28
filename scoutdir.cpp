#include <cstring>
#include <fstream>
#include <print>
#include <stdlib.h>
#include <curl/curl.h>
#include <string_view>
#include <vector>

int main(int argc, char *argv[])
{
    CURL *curl_handle;
    CURLcode curl_res;
    long http_code;
    std::vector<std::string_view> wordlist;

    std::println("scoutdir -- The free directory bruteforcer");

    if (argc <= 1) {
        std::println("Maybe try with an option? Use -h to list them all.");
        return EXIT_SUCCESS;
    }

    curl_handle = curl_easy_init();
    if (not curl_handle) {
        std::println(stderr, "ERROR: Could not initialize CURL handle.");
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
        } else if (std::strcmp(argv[i], "-u") == 0) {
            curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "HEAD");
            curl_easy_setopt(curl_handle, CURLOPT_URL, argv[i + 1]);
            curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

            curl_res = curl_easy_perform(curl_handle);
            if (curl_res != CURLE_OK) {
                std::println(stderr, "ERROR: {}", curl_easy_strerror(curl_res));
                return EXIT_FAILURE;
            }

            if (wordlist.empty()) {
                std::println(stderr, "ERROR: It looks like no wordlist has been provided."
                "Try again with -w <pathname>.");
                return EXIT_FAILURE;
            }

            curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);
            std::println("FOUND: {} ({})", argv[i + 1], http_code);
        }
    }

    curl_easy_cleanup(curl_handle);

    return EXIT_SUCCESS;
}