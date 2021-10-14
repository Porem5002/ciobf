#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char* src = ",+.";
    char* current_char_ptr = src;

    signed char cells[100] = {0};
    signed char* cell_ptr = cells;

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

                while(*current_char_ptr != ']') current_char_ptr++;

                current_char_ptr++;
                break;
            case ']':
                if(*cell_ptr == 0) break;
                
                while(*current_char_ptr != '[') current_char_ptr--;

                current_char_ptr++;
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

    return 0;
}
