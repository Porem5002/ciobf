#ifndef CIOBF_HEADER
#define CIOBF_HEADER

#include "options.h"
#include "platform.h"

typedef char limited_string_t [200];

#if defined(CPU_64_BITS)
void compile_64_bits(char* src, options_t* options);
#else
#define compile_64_bits compile_32_bits
#endif

void compile_32_bits(char* src, options_t* options);

#endif
