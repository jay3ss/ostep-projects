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


// char_count = 38;
// char c = 'a';
// fwrite(&char_count, sizeof(int), 1, stdout);
// putc(c, stdout);
// }



// int main(int argc, char* argv[]) {
//     if (argc <= 1) {
//         printf("wzip: file1 [file2 ...]\n");
//         exit(EXIT_FAILURE);
//     }

//     FILE* file = fopen(argv[1], "r");

//     if (file == NULL) { return 1; }

//     long length = get_filesize(argv[1]);
//     char* characters = malloc(sizeof(char) * length);
//     char curr_c;
//     char prev_c = -1;

//     int letter_count = 1;

//     // for each character, count the number of times it appears in a row
//     // adapted from: https://stackoverflow.com/a/15713419
//     curr_c = fgetc(file);
// while (curr_c != EOF) {
//     if (curr_c == prev_c) {
//         letter_count++;
//     }
//     else if (curr_c != prev_c || curr_c == EOF) {
//         // sprintf(characters, "%i%c", letter_count, (char)curr_c);
//         letter_count = 1;
//     }

//     curr_c = fgetc(file);
//     if (curr_c != EOF) {
//         prev_c = curr_c;
//     }
// }

//     fwrite(&letter_count, sizeof(int), 1, stdout);
//     putc(prev_c, stdout);
//     // printf("\n%i%c\n", letter_count, prev_c);

//     fclose(file);
//     free(characters);

//     exit(EXIT_SUCCESS);
// }
