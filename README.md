# Brainfuck interpreter
Takes a file and runs [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) code. Interpreter written in C.

## Usage
Compile using `gcc` or any C compiler. Then run with file path as parameter
```
gcc interpreter.c -o bf
./bf <path_to_file>
```
You can also convert Brainfuck to simple C code
```
gcc converter.c -o bf_to_c
./bf_to_c <brainfuck_file> <path_to_output_file>
```
## Examples
Run Brainfuck
```
./bf hello_world.bf
```
Convert Brainfuck to C:
```
./bf_to_c hello_world.bf hello_world.c
```