#include <stdio.h>
#include <stdlib.h>

#include "options.h"
#include "ciobf.h"
#include "fileio.h"

int main(int argc, char** argv)
{
    if(argc < 2) exit(1);
    
    options_t options = load_options(argc, argv);

    char* src =  get_file_contents(options.input_file_name);
   
    if(options.interpret)
    {
        interpret(src, &options);
        return 0;
    } 
    
    switch(options.target_platform)
    {
        case PLATFORM_LINUX_64B:
            compile_to_linux_x86_64(src, &options);
            break;
        case PLATFORM_LINUX_32B:
            compile_to_linux_x86(src, &options);
            break;
        default:
            break;
    }    

    return 0;
}
