#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(FILE* file) {
    size_t length = 4096;
    char* line = malloc(sizeof(char) * length);

    while (fgets(line, length, file) != NULL) {
        printf("%s", line);
    }
    free(line);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            FILE* file = fopen(argv[i], "r");
            if (file == NULL) {
                puts("wcat: cannot open file");
                return 1;
            }
            print_file(file);
            fclose(file);
        }
    }

    return 0;
}