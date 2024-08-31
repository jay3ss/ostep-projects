#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// long get_filesize(char* filename) {
//     // adapted from:
//     // https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c#comment9125254_238607
//     int fd = open(filename, 'r');
//     long length = lseek(fd, 0, SEEK_END) + 1;
//     close(fd);
//     return length;
// }

char END_OF_FILE = '\0';

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    FILE* file;
    int char_count = 0;
    char curr_c[2] = "";
    char prev_c[2] = "";

    for (int i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");

        if (file == NULL) { exit(EXIT_FAILURE); }

        while (fread(&curr_c, sizeof(char), 1, file)) {
            if (strcmp(curr_c, prev_c) == 0) {
                char_count++;
            }
            else {
                if (prev_c[0] != END_OF_FILE) {
                    fwrite(&char_count, sizeof(int), 1, stdout);
                    fwrite(prev_c, sizeof(char), 1, stdout);
                }
                char_count = 1;
                strcpy(prev_c, curr_c);
            }
        }
        fclose(file);
    }
    fwrite(&char_count, sizeof(int), 1, stdout);
    fwrite(prev_c, sizeof(char), 1, stdout);
    exit(0);
}
