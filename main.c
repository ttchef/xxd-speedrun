
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h> 
#include <stdbool.h>

#define MAX_LINE 20
#define MAX_STDIN_INPUT 3000

#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool subnstr(char* haystack, size_t haystack_size, char* needle, size_t needle_size, int32_t* index) {
    if (needle_size > haystack_size) {
        fprintf(stderr, "subnstr called with substr bigger than match str\n");
        return false;
    }

    int32_t chars_right;
    for (int32_t i = 0; i < haystack_size; i++) {
        chars_right = 0;
        for (int32_t j = 0; j < needle_size; j++) {
            if (i + needle_size - 1 >= haystack_size) {
                *index = -1;
                return false;
            }
            if (haystack[i + j] == needle[j]) chars_right++;
        }
        if (chars_right == needle_size) {
            *index = i;
            return true;
        }
    }
    *index = -1;
    return false;
}

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
    else if (argc > 1) {
        int32_t index = 1;
        if (argc == 4) {
            if (strcmp(argv[1], "-p") != 0) {
                fprintf(stderr, "BRO IF YOU USE 4 ARGUMENTS YOU NEED TO SPECIFY -p flag brother\n");
                fprintf(stderr, "Like: ./main -p <pattern> <filename>\n");
                exit(-1);
            }
            if (strlen(argv[2]) > 15) {
                fprintf(stderr, "pattern to long\n");
                exit(-1);
            }
            index = 3;
        }

        fd = fopen(argv[index], "rb");
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

    bool hightlite_next_line = false;
    int32_t highlite_index = 0;

    if (subnstr(buffer, MIN(size, 16), argv[2], strlen(argv[2]), &highlite_index)) {
        hightlite_next_line = true;
    }

    printf("Size of pattern: %zu\n", strlen(argv[2]));

    printf("%08X: ", hex_offset);
    for (int32_t i = 0; i < size; i++) {
        if (i > 16) hightlite_next_line = false;
        printf("%02X", buffer[i]);
        line[line_index++] = buffer[i];

        if ((i + 1) % 2 == 0) printf(" ");
        if ((i + 1) % 16 == 0) {
            if (subnstr(buffer + hex_offset, MIN(size - hex_offset, 16), argv[2], strlen(argv[2]), &highlite_index)) {
                hightlite_next_line = true;
            }

            print_line(line, &line_index);
            hex_offset += 16;

            if (hightlite_next_line) {
                printf("          "); // hex offset
                int32_t needle_index = highlite_index % 16;
                int j;
                for (j = 0; j < highlite_index; j++) {
                    printf("  ");
                    if (j % 4 == 0) printf(" ");
                }
                int tmp = j + 1;
                j += 1;
                for (; j < strlen(argv[2]) + tmp; j++) {
                    printf("^^");
                    if (j % 4 == 0) printf(" ");
                }
                for (; j <= 16; j++) {
                    printf("  ");
                    if (j % 4 == 0) printf(" ");
                }
                printf("   ");

                int x;
                for (x = 0; x < highlite_index; x++) {
                    printf(" ");
                }
                x += 1;
                for (; x < strlen(argv[2]) + tmp; x++) {
                    printf("^");
                }
                printf("\n");;
            }

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

