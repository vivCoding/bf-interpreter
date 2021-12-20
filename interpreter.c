#include "stdio.h"
#include "stdlib.h"

// local stack stuff
typedef struct item {
    int position;
    struct item *next;
} Item;

Item* stack = NULL;
int stack_length = 0;

Item* peek_stack() {
    return stack;
}

void push_stack(int position) {
    Item* item = malloc(sizeof(Item));
    item->position = position;
    item->next = stack;
    stack = item;
    stack_length++;
}

Item* pop_stack() {
    Item* popped = stack;
    stack = stack->next;
    stack_length--;
    return popped;
}

// brainfuck stuff
#define DATA_SIZE 30000
char *arr[DATA_SIZE];
int ptr = 0;
FILE *file;

int skip_to_close() {
    char c = fgetc(file);
    while (c != EOF) {
        if (c == '[') push_stack(-1);
        else if (c == ']' && pop_stack()->position != -1) return 1;
        c = fgetc(file);
    }
    return 0;
}

int execute_bf() {
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
                push_stack(ftell(file));
                if (arr[ptr] == 0 && !skip_to_close()) return 0;
                break;
            case ']':
                if (stack_length == 0) return 0;
                if (arr[ptr] != 0) fseek(file, peek_stack()->position, SEEK_SET);
                else pop_stack();
        }
        c = fgetc(file);
    }
    return 1;
}

int main (int argc, char* argv[]) {
    if (argc == 1) {
        printf("File error: No file specified!\n");
        return 1;
    }
    file = fopen(argv[1], "r");
    if (!file) {
        printf("File error: Cannot open file. Make sure it exists!\n");
        return 1;
    }

    if (!execute_bf() || stack_length != 0) {
        printf("\nRuntime error: Make sure you have correctly closing loop [] brackets!\n");
    }
    fclose(file);
    return 0;
}