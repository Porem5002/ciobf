#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/compile.h"
#include "include/compile_info.h"

static void simplify_src(char* destination, char* src)
{
   size_t i;
   size_t j;

   j = 0;   

   for(i = 0; i < strlen(src); i++)
   {
      switch(src[i])
      {
         case '+':
         case '-':
         case '>':
         case '<':
         case '.':
         case ',':
         case '[':
         case ']':
            destination[j] = src[i];
            j++;
            break;
         default:
            break;
      }
   }

   destination[j] = '\0';
}

#if defined(CPU_64_BITS)

void compile_64_bits(char* src, options_t* options)
{
    char simplified_src [strlen(src)+1];

    simplify_src(simplified_src, src);

    char* current_char_ptr = simplified_src;
   
    unsigned int current_max_loop_id = 0;
    unsigned int loop_id_stack [256] = {0};
    unsigned int* loop_id_stack_top = loop_id_stack;   
    
    bool requires_print = false;
    bool requires_read = false;

    limited_string_t asm_file_name;
    sprintf(asm_file_name, "%s.s", options->output_file_name);
    freopen(asm_file_name, "w", stdout);
   
    compile_64_bits_head(options);

/* ------------------------------------- */
/*        Body of assembly file          */
/* ------------------------------------- */

    while(*current_char_ptr != '\0')
    {
        bool compiled_common_command = check_and_compile_64_bits_common_command(&current_char_ptr);
        
        if(compiled_common_command) continue;

        switch(*current_char_ptr)
        {
            case '+':
            case '-':
                compile_64_bits_cell_increment(&current_char_ptr); 
                break;
            case '>':
            case '<':
                compile_64_bits_pointer_increment(&current_char_ptr); 
                break;
            case '[':
                compile_64_bits_loop_start(&loop_id_stack_top, &current_max_loop_id); 
                break;
            case ']':
                loop_id_stack_top--;
                printf("\tjmp loop%u\n", *loop_id_stack_top);
                printf("endloop%u:\n", *loop_id_stack_top);
                break;
            case '.':
                requires_print = true; 
                printf("\tcall print\n");         
                break;
            case ',':
                requires_read = true;
                printf("\tcall read_with_flush\n");
                break;
            default: 
                break;
        }
        
        current_char_ptr++;
    }
   
    compile_64_bits_footer(options, requires_print, requires_read);

    fclose(stdout);

    if(options->output_file_type == OUTPUT_ASM_FILE) return;

    assemble_64_bits(options);

    if(options->output_file_type == OUTPUT_OBJ_FILE) return; 
   
    link_64_bits(options);
}

#endif

void compile_32_bits(char* src, options_t* options)
{
   char simplified_src [strlen(src)+1];

   simplify_src(simplified_src, src);

   char* current_char_ptr = simplified_src;
   
   unsigned int current_max_loop_id = 0;
   unsigned int loop_id_stack [256] = {0};
   unsigned int* loop_id_stack_top = loop_id_stack;   
    
   bool requires_print = false;
   bool requires_read = false;

   char asm_file_name [strlen(options->output_file_name) + 3];
   sprintf(asm_file_name, "%s.s", options->output_file_name);
   freopen(asm_file_name, "w", stdout);
   
    compile_32_bits_head(options);

/* ------------------------------------- */
/*        Body of assembly file          */
/* ------------------------------------- */

    while(*current_char_ptr != '\0')
    { 
        bool compiled_common_command = check_and_compile_32_bits_common_command(&current_char_ptr);
        
        if(compiled_common_command) continue;
        
        switch(*current_char_ptr)
        { 
            case '+':
            case '-':
                compile_32_bits_cell_increment(&current_char_ptr);
                break;
            case '>':
            case '<':
                compile_32_bits_pointer_increment(&current_char_ptr); 
                break;
            case '[':
                compile_32_bits_loop_start(&loop_id_stack_top, &current_max_loop_id); 
                break;
            case ']':
                loop_id_stack_top--;
                printf("\tjmp loop%u\n", *loop_id_stack_top);
                printf("endloop%u:\n", *loop_id_stack_top);
                break;
            case '.':
                requires_print = true; 
                printf("\tcall print\n"); 
                break;
            case ',':
                requires_read = true;
                printf("\tcall read_with_flush\n");
                break;
            default: 
                break;
        }
        
        current_char_ptr++;
    }
   
    compile_32_bits_footer(options, requires_print, requires_read); 

    fclose(stdout);

    if(options->output_file_type == OUTPUT_ASM_FILE) return;
    
    assemble_32_bits(options);
      
    if(options->output_file_type == OUTPUT_OBJ_FILE) return; 
   
    link_32_bits(options);
}

