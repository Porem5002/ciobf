#ifndef CIOBF_HEADER
#define CIOBF_HEADER

#include "options.h"

void interpret(char* src, options_t* options);

void compile_to_x86_64_bits(char* src, options_t* options);

void compile_to_x86_32_bits(char* src, options_t* options);

#endif
