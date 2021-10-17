#ifndef OPTIONS_HEADER
#define OPTIONS_HEADER

#include <stdint.h>
#include <stdbool.h>

enum
{
    PLATFORM_LINUX_64B,
    PLATFORM_LINUX_32B,
    PLATFORM_WINDOWS_64B,
    PLATFORM_WINDOWS_32B
};

#define DEFAULT_PLATFORM PLATFORM_LINUX_64B
/*
#if defined(__linux__) && INTPTR_MAX == UINT64_MAX
    #define DEFAULT_PLATFORM PLATFORM_LINUX_64B
#elif defined(__linux__) && INTPTR_MAX == UINT32_MAX
    #define DEFAULT_PLATFORM PLATFORM_LINUX_32B
#elif defined(WIN64)
    #define DEFAULT_PLATFORM PLATFORM_WINDOWS_64B
#elif defined(WIN32)
    #define DEFAULT_PLATFORM PLATFORM_WINDOWS_32B
#else
    #define DEFAULT_PLATFORM
#endif
*/

enum
{
    OUTPUT_EXECUTABLE,
    OUTPUT_OBJ_FILE,
    OUTPUT_ASM_FILE
};

typedef struct OPTIONS_STRUCT
{
    bool interpret;
    int target_platform;
    int cell_count;
    char* input_file_name;
    char* output_file_name;  
    int output_file_type; 
} options_t;

options_t load_options(int argc, char** argv);

#endif
