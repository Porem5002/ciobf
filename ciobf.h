#ifndef CIOBF_HEADER
#define CIOBF_HEADER

#include "options.h"

void interpret(char* src, options_t* options);

void compile_to_linux_x86_64(char* src, options_t* options);

void compile_to_linux_x86(char* src, options_t* options);

#endif
