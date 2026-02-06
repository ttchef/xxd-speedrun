
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h> 
#include <stdbool.h>

#define MAX_LINE 20
#define MAX_STDIN_INPUT 3000

void print_line(char* line, int32_t* idx) {
    char* l = line;
    
    if (*idx < 16) {
        for (int32_t i = *idx; i <= 16; i++) {
            printf("  ");
            if (i % 4 == 0 && i != 16) printf(" ");
        }
    }

    while (*l) {
        char c = *l++;
        if (isprint(c)) {
            printf("%c", c);
        }
        else {
            printf(".");
        }
    }
    printf("\n");
    *idx = 0;
    memset(line, 0, MAX_LINE);
}

int32_t main(int32_t argc, char** argv) {
    FILE* fd;
    bool stdin_read = false;
    int64_t size = 0;

    char* stdin_input;

    if (argc == 1) {
        stdin_input = calloc(MAX_STDIN_INPUT, 1);
        fgets(stdin_input, MAX_STDIN_INPUT, stdin);
        stdin_read = true;
        stdin_input[MAX_STDIN_INPUT - 1] = '\0';
        size = strlen(stdin_input);
        printf("Size: %ld\n", size);
    }
    else {
        fd = fopen(argv[1], "rb");
        if (!fd) {
            fprintf(stderr, "HOLY SHIT\n");
            exit(-1);
        }
        fseek(fd, 0, SEEK_END);
        size = ftell(fd);
        rewind(fd);
    }

    char buffer[size + 1];

    if (!stdin_read) {
        fread(buffer, 1, size, fd);
    }
    else {
        memcpy(buffer, stdin_input, size);
        free(stdin_input);
    }

    buffer[size] = '\0';

    char line[MAX_LINE];
    memset(line, 0, MAX_LINE);

    int32_t line_index = 0;
    int32_t hex_offset = 0;

    printf("%08X: ", hex_offset);
    for (int32_t i = 0; i < size; i++) {
        printf("%02X", buffer[i]);
        line[line_index++] = buffer[i];

        if ((i + 1) % 2 == 0) printf(" ");
        if ((i + 1) % 16 == 0) {
            print_line(line, &line_index);
            hex_offset += 16;
            printf("%08X: ", hex_offset);
        }
    }
    if (line_index != 0) {
        print_line(line, &line_index);
    }
    printf("\n");;

    if (!stdin_read) fclose(fd);
        
    return 0;
}

