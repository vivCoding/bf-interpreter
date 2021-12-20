CFLAGS = -Wall -std=gnu99 -g -w
CC = gcc
OUTPUT_DIR = bin

interpreter:
	@mkdir -p $(OUTPUT_DIR)
	@$(CC) interpreter.c $(CFLAGS) -o $(OUTPUT_DIR)/bf

converter:
	mkdir -p $(OUTPUT_DIR)
	$(CC) converter.c $(CFLAGS) -o $(OUTPUT_DIR)/bf_to_c

clean:
	rm -rf $(OUTPUT_DIR)