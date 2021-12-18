#include "stdio.h"

#define HEADERS "#include \"stdio.h\"\n"
#define OPEN_MAIN "int main() {"
#define VARS "int DATA_SIZE = 30000; char *arr[DATA_SIZE]; int ptr = 0;"
#define RIGHT "ptr = ptr == DATA_SIZE - 1 ? 0 : ++ptr;"
#define LEFT "ptr = ptr == 0 ? DATA_SIZE - 1 : --ptr;"
#define INC "arr[ptr]++;"
#define DEC "arr[ptr]--;"
#define OUTPUT "putchar((int) arr[ptr]);"
#define INPUT "arr[ptr] = (char) getchar();"
#define OPEN_WHILE "while (arr[ptr] != 0) {"
#define CLOSE_BRACKET "}"

int main (int argc, char* argv[]) {
    if (argc == 1) {
        printf("Error: No input file specified!\n");
        return 1;
    } else if (argc == 2) {
        printf("Error: No output file path specified!\n");
        return 1;
    }
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Cannot open file. Make sure it exists!\n");
        return 1;
    }

    FILE* out = fopen(argv[2], "w");
    fputs(HEADERS, out);
    fputs(OPEN_MAIN, out);
    fputs(VARS, out);

    // TODO: optimize some of this
    char c = fgetc(file);
    while (c != EOF) {
        switch (c) {
            case '>': fputs(RIGHT, out); break;
            case '<': fputs(LEFT, out); break;
            case '+': fputs(INC, out); break;
            case '-': fputs(DEC, out); break;
            case '.': fputs(OUTPUT, out); break;
            case ',': fputs(INPUT, out); break;
            case '[': fputs(OPEN_WHILE, out); break;
            case ']': fputs(CLOSE_BRACKET, out); break;
        }
        c = fgetc(file);
    }
    fputs(CLOSE_BRACKET, out);
    fclose(file);
    fclose(out);
    return 0;
}