#ifndef OPTIONS_HEADER
#define OPTIONS_HEADER

#include <stdint.h>
#include <stdbool.h>

#if defined(WIN64) || defined(WIN32)
#if defined(WIN64)
#define IS_CURRENT_PLATFORM_32_BITS false 
#elif defined(WIN32)
#define IS_CURRENT_PLATFORM_32_BITS true
#endif
#elif defined(__GNUC__)
#if defined(__x86_64__)
#define IS_CURRENT_PLATFORM_32_BITS false
#else
#define IS_CURRENT_PLATFORM_32_BITS true
#endif
#endif

enum
{
    OUTPUT_EXECUTABLE,
    OUTPUT_OBJ_FILE,
    OUTPUT_ASM_FILE
};

typedef uint32_t optint_t;

typedef struct OPTIONS_STRUCT
{
    bool interpret;
    bool is_target_platform_32_bits;
    optint_t cell_count;
    optint_t buffer_size;
    char* input_file_name;
    char* output_file_name;  
    optint_t output_file_type; 
} options_t;

options_t load_options(int argc, char** argv);

#endif
