#include"Headder.h"
// Function to get the size of a file
int get_file_size(char *filename) 
{
    FILE *fptr = fopen(filename, "r");
    if (!fptr) 
    {
        return FAILURE;
    }

    fseek(fptr, 0, SEEK_END);
    unsigned int size = ftell(fptr);
    fclose(fptr);

    return size > 0 ? SUCCESS : FAILURE;
}