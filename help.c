#include <stdio.h>

#include "include/help.h" 

void print_help()
{   
    printf("Usage: ciobf input_file [options]\n");
    printf("By default ciobf runs in Compilation mode, use the '-int' option to run in Interpretation mode.\n");
    printf("Options:\n");
    printf("   --help            ==> Display help information.\n");
    printf("   -h                ==> Display help information.\n");
    printf("   -int              ==> Run Interpretation mode.\n");
    printf("   -o <output_name>  ==> Set name of output files.\n");
    printf("   -c <cell_count>   ==> Set the amount of cells to 'cell_count', this should be a positive integer.\n");
    printf("   -b <byte_count>   ==> Set the buffer size for stdout to the 'byte_count', this should be a positive integer.\n");
    printf("   -asm              ==> Only generates the assembly file.\n");
    printf("   -obj              ==> Only generates the assembly file and the object file.\n");
    printf("   -bit32            ==> Forces compilation to 32-bits if the system is 64-bits, otherwise does nothing.\n");
}
