#include <stdio.h>
#include <stdlib.h>

#include "ciobf.h"
#include "fileio.h"

int main(int argc, char** argv)
{
    if(argc < 2) exit(1);

    char* src =  get_file_contents(argv[1]);
    
    compile_to_linux_x86_64(src);    

    return 0;
}
