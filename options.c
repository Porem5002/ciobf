#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "options.h"

options_t load_options(int argc, char** argv)
{
    options_t options;
    options.interpret = false;
    options.cell_count = 100;
    options.target_platform = DEFAULT_PLATFORM;
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
            options.cell_count = (int)strtoull(argv[++i], &p, 10);
            continue; 
        }

        if(strcmp(argv[i], "-p") == 0)
        {
            i++;

            if(strcmp(argv[i], "linux64") == 0)
            {
                options.target_platform = PLATFORM_LINUX_64B;   
                continue;
            }
            
            if(strcmp(argv[i], "linux32") == 0)
            {
                options.target_platform = PLATFORM_LINUX_32B;   
                continue;
            }

            if(strcmp(argv[i], "win64") == 0)
            {
                options.target_platform = PLATFORM_WINDOWS_64B;   
                continue;
            }
            
            if(strcmp(argv[i], "win32") == 0)
            {
                options.target_platform = PLATFORM_WINDOWS_32B;   
                continue;
            }
        
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
