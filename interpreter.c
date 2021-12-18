#include "stdio.h"

#define DATA_SIZE 30000
char* arr[DATA_SIZE];
int ptr = 0;
FILE* file;

void skip_to_close() {
    char c = fgetc(file);
    while (c != EOF) {
        if (c == '[') skip_to_close();
        else if (c == ']') return;
        c = fgetc(file);
    }
}

void execute_bf() {
    char c = fgetc(file);
    while (c != EOF) {
        switch (c) {
            case '>': ptr = ptr == DATA_SIZE - 1 ? 0 : ++ptr; break;
            case '<': ptr = ptr == 0 ? DATA_SIZE - 1 : --ptr; break;
            case '+': arr[ptr]++; break;
            case '-': arr[ptr]--; break;
            case '.': putchar((int) arr[ptr]); break;
            case ',': arr[ptr] = (char) getchar(); break;
            case '[':
                int starting = ftell(file);
                if (arr[ptr] == 0) {
                    skip_to_close();
                }
                while (arr[ptr] != 0) {
                    fseek(file, starting, SEEK_SET);
                    execute_bf();
                }
                break;
            case ']': return;
        }
        c = fgetc(file);
    }
}

int main (int argc, char* argv[]) {
    if (argc == 1) {
        printf("Error: No file specified!\n");
        return 1;
    }
    file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Cannot open file. Make sure it exists!\n");
        return 1;
    }

    execute_bf();
    fclose(file);
    return 0;
}