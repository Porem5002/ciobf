#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "compile.h"
#include "platform.h"
#include "string_op.h"

#if defined(LINUX_OS)

#if defined(CPU_64_BITS)

void compile_64_bits_head(options_t* options)
{
    printf("section .bss\n");
    printf("array resb %u\n", options->cell_count);
    printf("buffer resb %u\n", options->buffer_size);
    printf("section .text\n");
    printf("global _start\n");
    printf("_start:\n");
    printf("\tmov rbx, buffer\n");
    printf("\tmov rsi, array\n");
    printf("\txor rcx, rcx\n");
}

bool check_and_compile_64_bits_common_command(char** current_char_ptr)
{
    if(string_starts_with(*current_char_ptr, "[-]"))
    {
        printf("\tmov byte [rsi], 0\n");
        *current_char_ptr += strlen("[-]");
        return true;
    }

    if(string_starts_with(*current_char_ptr, "[+]"))
    {
        printf("\tmov byte [rsi], 255\n");
        *current_char_ptr += strlen("[+]");
        return true;
    }

    return false;
}

void compile_64_bits_cell_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '+' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '+' || **current_char_ptr == '-');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd byte [rsi], %u\n", increment);
    else if (increment < 0)
        printf("\tsub byte [rsi], %u\n", -increment);
}

void compile_64_bits_pointer_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '>' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '>' || **current_char_ptr == '<');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd rsi, %u\n", increment);
    else if (increment < 0)
        printf("\tsub rsi, %u\n", -increment);
}

void compile_64_bits_loop_start(unsigned int** loop_id_stack_top, unsigned int* current_max_loop_id)
{
    printf("loop%u:\n", *current_max_loop_id);
    printf("\tcmp byte [rsi], 0\n");
    printf("\tjz endloop%u\n", *current_max_loop_id);

    **loop_id_stack_top = *current_max_loop_id;
    (*loop_id_stack_top)++;
    (*current_max_loop_id)++;
}

void compile_64_bits_footer(options_t* options, bool requires_print, bool requires_read)
{
    if(requires_print)
    {
        printf("\tcmp rcx, 0\n");
        printf("\tje exit_flush\n");
        printf("\tmov rax, 1\n");
        printf("\tmov rdi, 1\n");
        printf("\tmov rsi, buffer\n");
        printf("\tmov rdx, rcx\n");
        printf("\tsyscall\n");
        printf("exit_flush:\n");
    }

    /* Exit Syscall */
    printf("\tmov rax, 60\n");
    printf("\txor rdi, rdi\n");
    printf("\tsyscall\n");

    if(requires_print)
    {
        /* Print Function */ 
        printf("print:\n");
        printf("\tmov al, byte [rsi]\n");
        printf("\tmov byte [rbx], al\n");
        printf("\tinc rbx\n");
        printf("\tinc rcx\n");
        printf("\tcmp rbx, buffer + %u\n", options->buffer_size);
        printf("\tjne endprint\n");
        printf("\tpush rsi\n");
        printf("\tmov rax, 1\n");
        printf("\tmov rdi, 1\n");
        printf("\tmov rsi, buffer\n");
        printf("\tmov rdx, %u\n", options->buffer_size);
        printf("\tsyscall\n");
        printf("\tpop rsi\n");   
        printf("\tmov rbx, buffer\n");
        printf("\txor rcx, rcx\n"); 
        printf("endprint:\n");
        printf("\tret\n");
    }

    if(requires_read)
    {
        /* Read Function */
        printf("read_with_flush:\n");

        if(requires_print)
        {      
            printf("\tcmp rcx, 0\n");
            printf("\tje read\n");
            printf("\tpush rsi\n");
            printf("\tmov rax, 1\n");
            printf("\tmov rdi, 1\n");
            printf("\tmov rsi, buffer\n");
            printf("\tmov rdx, rcx\n");
            printf("\tsyscall\n");
            printf("\tmov rbx, buffer\n");
            printf("\txor rcx, rcx\n");
            printf("\tpop rsi\n");
        }

        printf("read:\n");
        printf("\txor rax, rax\n");
        printf("\txor rdi, rdi\n");
        printf("\tmov rdx, 1\n");
        printf("\tsyscall\n");
        printf("\tmov al, byte [rsi]\n");
        printf("\tcmp al, 10\n");
        printf("\tje read\n");
        printf("\tcmp al, 13\n");
        printf("\tje read\n");   
        printf("\tret\n");
    }
}

void assemble_64_bits(options_t* options)
{
    limited_string_t nasm_system_call_str;
    sprintf(nasm_system_call_str, "nasm -f elf64 %s.s -o %s.o", options->output_file_name, options->output_file_name);
    system(nasm_system_call_str);  
}

void link_64_bits(options_t* options)
{
    limited_string_t ld_system_call_str;
    sprintf(ld_system_call_str, "ld %s.o -o %s", options->output_file_name, options->output_file_name);
    system(ld_system_call_str);
}

#endif

void compile_32_bits_head(options_t* options)
{
    printf("section .bss\n");
    printf("array resb %u\n", options->cell_count);
    printf("buffer resb %u\n", options->buffer_size);
    printf("section .text\n");
    printf("global _start\n");
    printf("_start:\n");
    printf("\tmov esi, buffer\n");
    printf("\tmov ecx, array\n");
}

bool check_and_compile_32_bits_common_command(char** current_char_ptr)
{
    if(string_starts_with(*current_char_ptr, "[-]"))
    {
        printf("\tmov byte [ecx], 0\n");
        *current_char_ptr += strlen("[-]");
        return true;
    }

    if(string_starts_with(*current_char_ptr, "[+]"))
    {
        printf("\tmov byte [ecx], 255\n");
        *current_char_ptr += strlen("[+]");
        return true;
    }

    return false;
}

void compile_32_bits_cell_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '+' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '+' || **current_char_ptr == '-');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd byte [ecx], %u\n", increment);
    else if (increment < 0)
        printf("\tsub byte [ecx], %u\n", -increment);
}

void compile_32_bits_pointer_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '>' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '>' || **current_char_ptr == '<');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd ecx, %u\n", increment);
    else if (increment < 0)
        printf("\tsub ecx, %u\n", -increment);
}

void compile_32_bits_loop_start(unsigned int** loop_id_stack_top, unsigned int* current_max_loop_id)
{
    printf("loop%u:\n", *current_max_loop_id);
    printf("\tcmp byte [ecx], 0\n");
    printf("\tjz endloop%u\n", *current_max_loop_id);

    **loop_id_stack_top = *current_max_loop_id;
    (*loop_id_stack_top)++;
    (*current_max_loop_id)++;
}

void compile_32_bits_footer(options_t* options, bool requires_print, bool requires_read)
{
    if(requires_print)
    {
      printf("\tcmp edi, 0\n");
      printf("\tje exit_flush\n");
      printf("\tmov eax, 4\n");
      printf("\tmov ebx, 1\n");
      printf("\tmov ecx, buffer\n");
      printf("\tmov edx, edi\n");
      printf("\tint 0x80\n");
      printf("exit_flush:\n");
    }

    /* Exit Syscall */
    printf("\tmov eax, 1\n");
    printf("\txor ebx, ebx\n");
    printf("\tint 0x80\n");

    if(requires_print)
    {
       /* Print Function */ 
        printf("print:\n");
        printf("\tmov al, byte [ecx]\n");
        printf("\tmov byte [esi], al\n");
        printf("\tinc esi\n");
        printf("\tinc edi\n");
        printf("\tcmp esi, buffer + %u\n", options->buffer_size);
        printf("\tjne endprint\n");
        printf("\tpush ecx\n");
        printf("\tmov eax, 4\n");
        printf("\tmov ebx, 1\n");
        printf("\tmov ecx, buffer\n");
        printf("\tmov edx, %u\n", options->buffer_size);
        printf("\tint 0x80\n");
        printf("\tpop ecx\n");   
        printf("\tmov esi, buffer\n");
        printf("\txor edi, edi\n"); 
        printf("endprint:\n");
        printf("\tret\n");
    }


    if(requires_read)
    {
      /* Read Function */
        printf("read_with_flush:\n");
      
        if(requires_print)      
        {
            printf("\tcmp edi, 0\n");
            printf("\tje read\n");
            printf("\tpush ecx\n");
            printf("\tmov eax, 4\n");
            printf("\tmov ebx, 1\n");
            printf("\tmov ecx, buffer\n");
            printf("\tmov edx, edi\n");
            printf("\tint 0x80\n");
            printf("\tmov esi, buffer\n");
            printf("\txor edi, edi\n");
            printf("\tpop ecx\n");
        }

        printf("read:\n");
        printf("\tmov eax, 3\n");
        printf("\tmov ebx, 2\n");
        printf("\tmov edx, 1\n");
        printf("\tint 0x80\n");
        printf("\tmov al, byte [ecx]\n");
        printf("\tcmp al, 10\n");
        printf("\tje read\n");
        printf("\tcmp al, 13\n");
        printf("\tje read\n");   
        printf("\tret\n");
    }
}

void assemble_32_bits(options_t* options)
{
    limited_string_t nasm_system_call_str;
    sprintf(nasm_system_call_str, "nasm -f elf32 %s.s -o %s.o", options->output_file_name, options->output_file_name);
    system(nasm_system_call_str);  
}

void link_32_bits(options_t* options)
{
    limited_string_t ld_system_call_str;
    sprintf(ld_system_call_str, "ld -m elf_i386 %s.o -o %s", options->output_file_name, options->output_file_name);
    system(ld_system_call_str);
}

#elif defined(WINDOWS_OS)

#if defined(CPU_64_BITS)

void compile_64_bits_head(options_t* options)
{
    printf("section .bss\n");
    printf("stdin resq 1\n");
    printf("array resb %u\n", options->cell_count);
    printf("buffer resb %u\n", options->buffer_size);
    printf("bytes_written_holder resq 1\n");
    printf("section .text\n");
    printf("global _start\n");
    printf("extern ExitProcess\n");
    printf("extern WriteConsoleA\n");
    printf("extern ReadConsoleA\n");
    printf("extern GetStdHandle\n");
    printf("_start:\n");
    printf("\tsub rsp, 40\n");
    printf("\tmov rbx, array\n");
    printf("\tmov rbp, buffer\n");
    printf("\txor rsi, rsi\n");
    printf("\tmov rcx, -11\n");
    printf("\tcall GetStdHandle\n");
    printf("\tmov rdi, rax\n");
    printf("\tmov rcx, -10\n");
    printf("\tcall GetStdHandle\n");
    printf("\tmov qword [stdin], rax\n");
}

bool check_and_compile_64_bits_common_command(char** current_char_ptr)
{
    if(string_starts_with(*current_char_ptr, "[-]"))
    {
        printf("\tmov byte [rbx], 0\n");
        *current_char_ptr += strlen("[-]");
        return true;
    }

    if(string_starts_with(*current_char_ptr, "[+]"))
    {
        printf("\tmov byte [rbx], 255\n");
        *current_char_ptr += strlen("[+]");
        return true;
    }

    return false;
}

void compile_64_bits_cell_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '+' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '+' || **current_char_ptr == '-');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd byte [rbx], %u\n", increment);
    else if (increment < 0)
        printf("\tsub byte [rbx], %u\n", -increment);
}

void compile_64_bits_pointer_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '>' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '>' || **current_char_ptr == '<');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd rbx, %u\n", increment);
    else if (increment < 0)
        printf("\tsub rbx, %u\n", -increment);
}

void compile_64_bits_loop_start(unsigned int** loop_id_stack_top, unsigned int* current_max_loop_id)
{
    printf("loop%u:\n", *current_max_loop_id);
    printf("\tcmp byte [rbx], 0\n");
    printf("\tjz endloop%u\n", *current_max_loop_id);

    **loop_id_stack_top = *current_max_loop_id;
    (*loop_id_stack_top)++;
    (*current_max_loop_id)++;
}

void compile_64_bits_footer(options_t* options, bool requires_print, bool requires_read)
{
    if(requires_print)
    {
        printf("\tcmp rsi, 0\n");
        printf("\tje exit_flush\n");
        printf("\tmov rcx, rdi\n");
        printf("\tmov rdx, buffer\n");
        printf("\tmov r8, rsi\n");
        printf("\tmov r9, bytes_written_holder\n");
        printf("\tmov qword [rsp + 32], 0\n");
        printf("\tcall WriteConsoleA\n");
        printf("exit_flush:\n");
    }

    /* Exit Syscall */
    printf("\tmov rcx, 0\n");
    printf("\tcall ExitProcess\n");

    if(requires_print)
    {
        /* Print Function */ 
        printf("print:\n");
        printf("\tmov al, byte [rbx]\n");
        printf("\tmov byte [rbp], al\n");
        printf("\tinc rbp\n");
        printf("\tinc rsi\n");
        printf("\tcmp rbp, buffer + %u\n", options->buffer_size);
        printf("\tjne endprint\n");
        printf("\tmov rcx, rdi\n");
        printf("\tmov rdx, buffer\n");
        printf("\tmov r8, %u\n", options->buffer_size);
        printf("\tmov r9, bytes_written_holder\n");
        printf("\tmov qword [rsp + 32], 0\n");
        printf("\tcall WriteConsoleA\n");  
        printf("\tmov rbp, buffer\n");
        printf("\txor rsi, rsi\n"); 
        printf("endprint:\n");
        printf("\tret\n");
    }

    if(requires_read)
    {
        /* Read Function */
        printf("read_with_flush:\n");
      
        if(requires_print)      
        {
            printf("\tcmp rsi, 0\n");
            printf("\tje read\n");
            printf("\tmov rcx, rdi\n");
            printf("\tmov rdx, buffer\n");
            printf("\tmov r8, rsi\n");
            printf("\tmov r9, bytes_written_holder\n");
            printf("\tmov qword [rsp + 32], 0\n");
            printf("\tcall WriteConsoleA\n");
            printf("\tmov rbp, buffer\n");
            printf("\txor rsi, rsi\n");
        }

        printf("read:\n");
        printf("\tmov rcx, qword [stdin]\n");
        printf("\tmov rdx, rbx\n");
        printf("\tmov r8, 1\n");
        printf("\tmov r9, bytes_written_holder\n");
        printf("\tmov qword [rsp + 32], 0\n"); 
        printf("\tcall ReadConsoleA\n");
        printf("\tmov al, byte [rbx]\n");
        printf("\tcmp al, 10\n");
        printf("\tje read\n");
        printf("\tcmp al, 13\n");
        printf("\tje read\n");   
        printf("\tret\n");
    }
}

void assemble_64_bits(options_t* options)
{
    limited_string_t nasm_system_call_str;
    sprintf(nasm_system_call_str, "nasm -f win64 %s.s -o %s.obj", options->output_file_name, options->output_file_name);
    system(nasm_system_call_str);  
}

void link_64_bits(options_t* options)
{
    limited_string_t golink_system_call_str;
    sprintf(golink_system_call_str, "GoLink /console /entry _start %s.obj kernel32.dll", options->output_file_name);
    system(golink_system_call_str);
}

#endif

void compile_32_bits_head(options_t* options)
{
    printf("section .bss\n");
    printf("stdin resd 1\n");
    printf("array resb %u\n", options->cell_count);
    printf("buffer resb %u\n", options->buffer_size);
    printf("bytes_written_holder resd 1\n");
    printf("section .text\n");
    printf("global _start\n");
    printf("extern ExitProcess\n");
    printf("extern WriteConsoleA\n");
    printf("extern ReadConsoleA\n");
    printf("extern GetStdHandle\n");
    printf("_start:\n");
    printf("\tmov ebx, array\n");
    printf("\tmov ebp, buffer\n");
    printf("\txor esi, esi\n");
    printf("\tpush -11\n");
    printf("\tcall GetStdHandle\n");
    printf("\tmov edi, eax\n");
    printf("\tpush -10\n");
    printf("\tcall GetStdHandle\n");
    printf("\tmov dword [stdin], eax\n");
}

bool check_and_compile_32_bits_common_command(char** current_char_ptr)
{
    if(string_starts_with(*current_char_ptr, "[-]"))
    {
        printf("\tmov byte [ebx], 0\n");
        *current_char_ptr += strlen("[-]");
        return true;
    }

    if(string_starts_with(*current_char_ptr, "[+]"))
    {
        printf("\tmov byte [ebx], 255\n");
        *current_char_ptr += strlen("[+]");
        return true;
    }

    return false;
}

void compile_32_bits_cell_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '+' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '+' || **current_char_ptr == '-');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd byte [ebx], %u\n", increment);
    else if (increment < 0)
        printf("\tsub byte [ebx], %u\n", -increment);
}

void compile_32_bits_pointer_increment(char** current_char_ptr)
{
    int increment = 0;
            
    do 
    {  
        increment += **current_char_ptr == '>' ? 1 : -1;
        (*current_char_ptr)++;
    }
    while(**current_char_ptr == '>' || **current_char_ptr == '<');
            
    (*current_char_ptr)--;
            
    if(increment > 0)
        printf("\tadd ebx, %u\n", increment);
    else if (increment < 0)
        printf("\tsub ebx, %u\n", -increment);
}

void compile_32_bits_loop_start(unsigned int** loop_id_stack_top, unsigned int* current_max_loop_id)
{
    printf("loop%u:\n", *current_max_loop_id);
    printf("\tcmp byte [ebx], 0\n");
    printf("\tjz endloop%u\n", *current_max_loop_id);

    **loop_id_stack_top = *current_max_loop_id;
    (*loop_id_stack_top)++;
    (*current_max_loop_id)++;
}

void compile_32_bits_footer(options_t* options, bool requires_print, bool requires_read)
{
    if(requires_print)
    {
        printf("\tcmp esi, 0\n");
        printf("\tje exit_flush\n");
        printf("\tpush 0\n");
        printf("\tpush bytes_written_holder\n");
        printf("\tpush esi\n");
        printf("\tpush buffer\n");
        printf("\tpush edi\n");
        printf("\tcall WriteConsoleA\n");
        printf("exit_flush:\n");
    }

    /* Exit Syscall */
    printf("\tpush 0\n");
    printf("\tcall ExitProcess\n");

    if(requires_print)
    {
        /* Print Function */ 
        printf("print:\n");
        printf("\tmov al, byte [ebx]\n");
        printf("\tmov byte [ebp], al\n");
        printf("\tinc ebp\n");
        printf("\tinc esi\n");
        printf("\tcmp ebp, buffer + %u\n", options->buffer_size);
        printf("\tjne endprint\n");
        printf("\tpush 0\n");
        printf("\tpush bytes_written_holder\n");
        printf("\tpush %u\n", options->buffer_size);
        printf("\tpush buffer\n");
        printf("\tpush edi\n");
        printf("\tcall WriteConsoleA\n");  
        printf("\tmov ebp, buffer\n");
        printf("\txor esi, esi\n"); 
        printf("endprint:\n");
        printf("\tret\n");
    }

    if(requires_read)
    {
        /* Read Function */
        printf("read_with_flush:\n");
      
        if(requires_print)      
        {
            printf("\tcmp esi, 0\n");
            printf("\tje read\n");
            printf("\tpush 0\n");
            printf("\tpush bytes_written_holder\n");
            printf("\tpush esi\n");
            printf("\tpush buffer\n");
            printf("\tpush edi\n");
            printf("\tcall WriteConsoleA\n");
            printf("\tmov ebp, buffer\n");
            printf("\txor esi, esi\n");
        }

        printf("read:\n");
        printf("\tpush 0\n");
        printf("\tpush bytes_written_holder\n");
        printf("\tpush 1\n");
        printf("\tpush ebx\n");
        printf("\tpush dword [stdin]\n");
        printf("\tcall ReadConsoleA\n");
        printf("\tmov al, byte [ebx]\n");
        printf("\tcmp al, 10\n");
        printf("\tje read\n");
        printf("\tcmp al, 13\n");
        printf("\tje read\n");   
        printf("\tret\n");
    }
}

void assemble_32_bits(options_t* options)
{
    limited_string_t nasm_system_call_str;
    sprintf(nasm_system_call_str, "nasm -f win32 %s.s -o %s.obj", options->output_file_name, options->output_file_name);
    system(nasm_system_call_str);  
}

void link_32_bits(options_t* options)
{
    limited_string_t golink_system_call_str;
    sprintf(golink_system_call_str, "GoLink /console /entry _start %s.obj kernel32.dll", options->output_file_name);
    system(golink_system_call_str);
}

#endif
