#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hex_dump(FILE *file) {
    unsigned char buffer[16];
    size_t offset = 0;

    while (!feof(file)) {
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
        if (bytesRead == 0) {
            break;
        }

        printf("%08zX: ", offset);

        for (size_t i = 0; i < bytesRead; ++i) {
            printf("%02X ", buffer[i]);
        }

        printf("|");

        for (size_t i = 0; i < bytesRead; ++i) {
            if (buffer[i] >= 32 && buffer[i] <= 126) {
                printf("%c", buffer[i]);
            } else {
                printf(".");
            }
        }

        printf("|\n");

        offset += bytesRead;
    }
}//end of void

void binary_dump(FILE *file) {
    unsigned char buffer[16];
    size_t offset = 0;

    while (!feof(file)) {
        size_t bytesRead = fread(buffer, 1, sizeof(buffer), file);
        if (bytesRead == 0) {
            break;
        }

        printf("%08zX: ", offset);

        for (size_t i = 0; i < bytesRead; ++i) {
            for (int j = 7; j >= 0; --j) {
                printf("%d", (buffer[i] >> j) & 1);
            }
            printf(" ");
        }

        printf("\n");

        offset += bytesRead;
    }
}//end of void 

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename> <-H|-B>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *print_mode = argv[2];

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    if (strcmp(print_mode, "-H") == 0) {
        hex_dump(file);
    } else if (strcmp(print_mode, "-B") == 0) {
        binary_dump(file);
    } else {
        printf("Invalid print_mode. Use -H for HEX DUMP or -B for binary dump.\n");
    }

    fclose(file);
    return 0;
}//end of main 
