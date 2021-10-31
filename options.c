#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "include/options.h"

options_t load_options(int argc, char** argv)
{
    options_t options;
    options.interpret = false;
    options.is_target_platform_32_bits = IS_CURRENT_PLATFORM_32_BITS;
    options.cell_count = 500;
    options.buffer_size = 200;
    options.input_file_name = NULL; 
    options.output_file_name = "out";   
    options.output_file_type = OUTPUT_EXECUTABLE;

    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] != '-')
        {
            options.input_file_name = argv[i];
            continue;
        }

        if(strcmp(argv[i], "-asm") == 0)
        {
            options.output_file_type = OUTPUT_ASM_FILE;
            continue;
        }
        
        if(strcmp(argv[i], "-obj") == 0)
        {
            options.output_file_type = OUTPUT_OBJ_FILE;
            continue;
        }
        
        if(strcmp(argv[i], "-int") == 0)
        {
            options.interpret = true;
            continue;
        }

        if(strcmp(argv[i], "-c") == 0)
        {
            char* p;
            options.cell_count = (optint_t)strtoull(argv[++i], &p, 10);
            continue; 
        }

        if(strcmp(argv[i], "-b") == 0)
        {
            char* p;
            options.buffer_size = (optint_t)strtoull(argv[++i], &p, 10);
            continue; 
        }

        if(strcmp(argv[i], "-bit32") == 0)
        {
            options.is_target_platform_32_bits = true;
            continue;
        }
        
        if(strcmp(argv[i], "-o") == 0)
        {   
            options.output_file_name = argv[++i];
            continue;
        }
    }
    
    return options;
} 
