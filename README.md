# ciobf
This program is a [Brainf#ck](https://en.wikipedia.org/wiki/Brainfuck) compiler and interpretor made in c.

# Installation
To install the prgram just run make.

Make sure to also install the [NASM](https://nasm.us/) assembler and the [ld](https://www.gnu.org/software/binutils/) linker.

# Usage

## Compiler

To run the compiler you just need to specify the name of the file containing the source code as a command line argument of the program.
```
$ ciobf name_of_file
```
To change the name of the output file just run the previous expression followed by the "-o" flag and the name to be applied:
```
$ ciobf name_of_file -o output_file_name
```
This operation will generate the assembly file, the object file and the final executable.

## Interpretor

If you want to run the interpretor instead use the "-int" flag like this:
```
$ ciobf name_of_file -int
```  

## Other Flags:

### The "-asm" flag:

By default the compiler will generate 3 files: the assembly file, the object file and the final executable.
What this flag does, is that it tells the compiler to ignore the assembling and linking stages and generate only the assembly file.

This flag has no effect in interpretation mode.

### The "-obj" flag:

Similar to the "-asm" flag, but makes the compiler ignore the linking stage only.
Generating the assembly file and the object file as a result.

This flag has no effect in interpretation mode.

### The "-p" flag:

This flag allows the user to specify manually the target platform of the files to be generated.

To use this flag effectibly write the flag followed by one of this expressions, depending on the desired platform:
* linux64 (for Linux 64-bit x86) 
* linux32 (for Linux 32-bit x86)
* win64 (for Windows 64-bit x86) not implemented yet
* win32 (for Windows 32-bit x86) not implemented yet

Example of its usage:
```
$ ciobf name_of_file -p linux32
```

If this flag is not used the program will automatically select the option that better fits the OS in which it is being run.

This flag has no effect in interpretation mode.

### The "-c" flag:

The purpose of this flag is to specify the amount of cells used by the program.

Example of its usage, setting the number of cells to 500:
```
$ ciobf name_of_file -c 500
```

This flag works both in compilation mode and interpretation mode.

