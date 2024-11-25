#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define Buffer 16
int main(int x, char *y[]) {
    int file;
    if (x != 2) {
        file = STDIN_FILENO;
    } else {
        file = open(y[1], O_RDONLY);
        if (file < 1) {
            return EXIT_FAILURE;
        }
    }
    ssize_t file_size;
    int name = 0;
    unsigned char buff[Buffer];
    while ((file_size = read(file, buff, Buffer)) > 0) {
        for (ssize_t i = file_size; i < Buffer; i++) {
            unsigned char index;
            if (read(file, &index, 1) > 0) {
                buff[i] = index;
                file_size++;
            }
        }
        printf("%08x: ", name);
        int space = 41;
        for (int j = 0; j < file_size; j = j + 2) {
            if (j + 1 < file_size) {
                printf("%02x%02x ", buff[j], buff[j + 1]);
                space = space - 5;
            } else {
                printf("%02x", buff[j]);
                j = j - 1;
                space = space - 2;
            }
        }
        while (space != 0) {
            printf(" ");
            space = space - 1;
        }
        for (int k = 0; k < file_size; k++) {
            if (buff[k] >= 32 && buff[k] <= 126) {
                printf("%c", buff[k]);
            } else {
                printf(".");
            }
        }
        printf("\n");
        name = name + 16;
    }
    close(file);
}
