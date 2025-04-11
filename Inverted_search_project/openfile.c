#include"Headder.h"

// Function to check if a file exists and can be opened
int open_file(char *filename) 
{
    FILE *fptr = fopen(filename, "r");
    if (!fptr) 
    {
        return FAILURE;
    }
    fclose(fptr);
    return SUCCESS;
}