# ciobf
A [Brainf#ck](https://en.wikipedia.org/wiki/Brainfuck) compiler and interpretor fully written in c, that generates x86 assembly for the NASM asssembler.
Currently the compiler supports Linux 64-bits/32-bits and Windows 32-bits.

# Installation
To install you just need to run the make file:
```
$ make
```
Make sure to also install, and place on your PATH enviroment variable, the following programs: 
* [NASM](https://nasm.us/)
* [ld](https://linux.die.net/man/1/ld) (If you are using Linux)
* [GoLink](http://godevtool.com/) (if you are using Windows)

# Usage

When ciobf is executed, it can be in one of two modes, the interpretation mode that interprets the source code directly without generating any machine code, and the compilation mode that generates the machine code for the platform that it is currently running on.

By default the program runs in compilation mode, but if you want to run the interpretor instead, add the '-int' flag to the command:
```
$ ciobf src_file_name -int 
```

## Flags

ciobf offers multiple flags to change the behaviour of the program, some of those only work on compilation mode and others work on both modes.

### Compilation specific Flags

#### The '-o' flag:

With this flag you can specify the name of the output file of the compiler, if this flag is not used than the default value for the output file name is 'out'.

Example of the usage of this flag, by setting the name of the output file to 'hello':
```
$ ciobf src_file_name -o hello
```

#### The '-b' flag:

This flag allows you to specify the size of the buffer to be used by the '.'(print) instruction, if this flag is not used than the default size of the buffer is 200. 

Example of the usage of the flag, setting the buffer size to 30:
```
$ ciobf src_file_name -b 30
```

#### The '-asm' flag:

This flag makes the compiler stop before the assembling stage, generating only the assembly file. 

#### The '-obj' flag:

This flag makes the compiler stop before the linking stage, generating only the assembly file and the object file.

#### The '-bit32' flag:

This flag forces the compiler to compile to 32-bits instead of 64-bits, if the platform is already 32-bits this flag has no effect.  

### General Flags

#### The '-c' flag:

This flag allows you to specify the number of cells to be used by Brainfuck, the default number is 500. 

Example of the usage of the flag, setting the cell count to 1000:
```
$ ciobf src_file_name -c 1000
```
