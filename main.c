#include <stdio.h>
#include <stdlib.h>

#include "include/help.h"
#include "include/options.h"
#include "include/compile.h"
#include "include/interpret.h"
#include "include/fileio.h"

int main(int argc, char** argv)
{
    options_t options = load_options(argc, argv);

    if(options.print_help_requested)
    {
        print_help();
        return 0;
    }

    if(options.input_file_name == NULL)
    {
        printf("Error: No input file was provided!\n");
        return 1;
    }

    char* src =  get_file_contents(options.input_file_name); 
    
    if(options.interpret)
    {
        interpret(src, &options);
    } 
    else if(!options.is_target_platform_32_bits)
    {
        compile_64_bits(src, &options);
    }
    else
    {
        compile_32_bits(src, &options);
    }
        
    return 0;
}
