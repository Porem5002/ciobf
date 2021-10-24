#include <stdio.h>
#include <stdlib.h>

#include "options.h"
#include "compile.h"
#include "interpret.h"
#include "fileio.h"

int main(int argc, char** argv)
{
    if(argc < 2) exit(1);
    
    options_t options = load_options(argc, argv);

    char* src =  get_file_contents(options.input_file_name); 

    if(options.interpret)
    {
        interpret(src, &options);
    } 
    else if(!options.is_target_platform_32_bits)
    {
        compile_to_x86_64_bits(src, &options);
    }
    else
    {
        compile_to_x86_32_bits(src, &options);
    }
        
    return 0;
}
