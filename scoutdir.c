#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    CURL *curl_handle;
    CURLcode curl_res;
    long http_code;
    struct stat wordlist_stat;
    char *wordlist_buf;

    printf("scoutdir -- The free directory bruteforcer\n");

    if (argc <= 1) {
        printf("Maybe try with an option? Use -h to list them all.\n");
        return EXIT_SUCCESS;
    }

    curl_handle = curl_easy_init();
    if (!curl_handle) {
        fprintf(stderr, "ERROR: Could not initialize CURL handle.\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printf("Available options:\n"
            "-h                             show this message\n"
            "-w <pathname>                  set the wordlist\n"
            "-u <url>                       start URL\n"
            );
        } else if (strcmp(argv[i], "-w") == 0) {
            if (stat(argv[i + 1], &wordlist_stat) != 0) {
                fprintf(stderr, "ERROR: Could not get wordlist size\n");
                return EXIT_FAILURE;
            }

            wordlist_buf = malloc((size_t)wordlist_stat.st_size);
            FILE *wordlist = fopen(argv[i + 1], "r");
            if (!wordlist) {
                fprintf(stderr, "ERROR: Could not open wordlist\n");
                return EXIT_FAILURE;
            }
            fread(wordlist_buf, sizeof(wordlist_buf), 1, wordlist);
            fclose(wordlist);
        } else if (strcmp(argv[i], "-u") == 0) {
            curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "HEAD");
            curl_easy_setopt(curl_handle, CURLOPT_URL, argv[i + 1]);
            curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

            curl_res = curl_easy_perform(curl_handle);
            if (curl_res != CURLE_OK) {
                fprintf(stderr, "ERROR: %s\n", curl_easy_strerror(curl_res));
                return EXIT_FAILURE;
            }

            if (!wordlist_buf) {
                fprintf(stderr, "ERROR: It looks like no wordlist has been provided."
                "Try again with -w <pathname>.\n");
                return EXIT_FAILURE;
            }

            curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);
            printf("FOUND: %s (%ld)\n", argv[i + 1], http_code);
        }
    }

    curl_easy_cleanup(curl_handle);

    return EXIT_SUCCESS;
}