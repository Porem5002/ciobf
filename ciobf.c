#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void interpret(char* src)
{
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
}

void compile(char* src)
{
   char simplified_src [strlen(src)+1];
   int j = 0;   

   for(int i = 0; i < strlen(src); i++)
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
            simplified_src[j] = src[i];
            j++;
            break;
         default:
            break;
      }
   }

   simplified_src[j] = '\0';
   
   char* current_char_ptr = simplified_src;
   
   unsigned int current_max_loop_id = 0;
   unsigned int loop_id_stack [256];
   unsigned int* loop_id_stack_top = loop_id_stack;   

   int increment;
   char last_syscall = 2;
   
   freopen("out.s", "w", stdout);

   printf("section .bss\n");
   printf("array resq 100\n");
   printf("section .text\n");
   printf("global _start\n");
   printf("_start:\n");
   printf("\tmov rsi, array\n");
   printf("\tmov rdx, 1\n");

   while(*current_char_ptr != '\0')
   { 
      switch(*current_char_ptr)
      {
         case '+':
         case '-':
            increment = 0;

            do
            {
               increment += *current_char_ptr == '+' ? 1 : -1;
               current_char_ptr++;
            }
            while(*current_char_ptr == '+' || *current_char_ptr == '-');
            
            current_char_ptr--;

            if(increment > 0) 
               printf("\tadd byte [rsi], %u\n", increment);
            else if(increment < 0)
               printf("\tsub byte [rsi], %u\n", -increment);
            break;
         case '>':
         case '<':
            increment = 0;
            
            do 
            {  
               increment += *current_char_ptr == '>' ? 1 : -1;
               current_char_ptr++;
            }
            while(*current_char_ptr == '>' || *current_char_ptr == '<');
            
            current_char_ptr--;
            
            if(increment > 0)
               printf("\tadd rsi, %u\n", increment);
            else if (increment < 0)
               printf("\tsub rsi, %u\n", -increment);
            break;
         case '[':
            printf("loop%u:\n", current_max_loop_id);
            printf("\tcmp byte [rsi], 0\n");
            printf("\tjz endloop%u\n", current_max_loop_id);

            *loop_id_stack_top = current_max_loop_id;
            loop_id_stack_top++;
            current_max_loop_id++;
            break;
         case ']':
            loop_id_stack_top--;

            printf("\tjmp loop%u\n", *loop_id_stack_top);
            printf("endloop%u:\n", *loop_id_stack_top);
         case '.': 
            printf("\tmov rax, 1\n");
            if(last_syscall != 1)
            {
               printf("\tmov rdi, 1\n");
               last_syscall = 1;  
            }
            // printf("\tmov rdx, 1\n");
            printf("\tsyscall\n");
            break;
         case ',':
            printf("\tmov rax, 0\n");
            if(last_syscall != 0)
            {
               printf("\tmov rdi, 0\n");
               last_syscall = 0;
            }
            // printf("\tmov rdx, 1\n");
            printf("\tsyscall\n");
         default: 
            break;
      }
      current_char_ptr++;
   }
   
   printf("\tmov rax, 60\n");
   printf("\tmov rdi, 0\n");
   printf("\tsyscall\n");
   fclose(stdout);

   system("nasm -f elf64 out.s -o out.o");
   system("ld out.o -o out");
}
