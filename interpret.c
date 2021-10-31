#include <stdio.h>
#include <string.h>

#include "include/interpret.h"

void interpret(char* src, options_t* options)
{
    char* current_char_ptr = src;

    signed char cells[options->cell_count];
    
    memset(cells, 0, options->cell_count);    

    signed char* cell_ptr = cells;
    
    int loop_counter;

    while(*current_char_ptr != '\0')
    {
        switch(*current_char_ptr)
        {
            case '+':
               (*cell_ptr)++;
		        break;
	        case '-':
                (*cell_ptr)--;
		        break;
            case '>':
                cell_ptr++;
                break;
            case '<':
                cell_ptr--;
                break;
            case '[':
                if (*cell_ptr != 0) break;
                
                loop_counter = 0; 
        
                while(true)
                {
                    if(*current_char_ptr == '[')
                    {
                         loop_counter++;
                    }
                    else if(*current_char_ptr == ']')
                    {
                        loop_counter--;
                    }

                    if(loop_counter == 0) break;
                
                    current_char_ptr++;
                }
                break;
            case ']':
                if(*cell_ptr == 0) break;
                
                loop_counter = 0; 
        
                while(true)
                {
                    if(*current_char_ptr == ']')
                    {
                         loop_counter++;
                    }
                    else if(*current_char_ptr == '[')
                    {
                        loop_counter--;
                    }

                    if(loop_counter == 0) break;

                    current_char_ptr--;
                }
                break;
            case '.':
                putchar((char)(*cell_ptr));
                break;
            case ',':
                *cell_ptr = (signed char)getchar();
                break;
            default: break;
        }
        
        current_char_ptr++;
    }
}
