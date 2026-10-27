#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    printf("scout -- The free directory bruteforcer\n");

    if (argc <= 1) {
        printf("Maybe try with an option? Use --help to list them all.\n");
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printf("Available options:\n"
            "--help         show this message\n"
            );
        } else {
            fprintf(stderr, "ERROR: Invalid option: %s\n", argv[i]);
        }
    }

    return EXIT_SUCCESS;
}