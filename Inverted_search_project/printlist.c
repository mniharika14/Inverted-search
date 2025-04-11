#include"Headder.h"

// Function to print the list of valid files
int print_list(file_list_t *head) 
{
    if (!head) 
    {
        printf("No valid files to display.\n");
        return FAILURE;
    }

    printf("The list of valid files:\nHead -> ");
    while (head) 
    {
        printf("%s -> ", head->file_name);
        head = head->filelink;
    }
    printf("NULL\n");
    return SUCCESS;
}