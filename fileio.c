#include <stdio.h>
#include <stdlib.h>
#include "fileio.h"

char* get_file_contents(char* path)
{
   FILE* f = fopen(path, "rb");
   size_t size;

   fseek(f, 0, SEEK_END);
   size = ftell(f);
   fseek(f, 0, SEEK_SET);
   
   char* buffer = malloc((size+1) * sizeof(char));   

   fread(buffer, size, 1, f);
   
   fclose(f);

   return buffer;
}
