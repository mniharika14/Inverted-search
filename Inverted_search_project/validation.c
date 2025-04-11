#include "Headder.h"

// Function to read and validate the files passed as arguments
int read_and_validate(int argc, char *argv[], file_list_t **head) 
{
    // Validate if at least one file is provided as input
    if (argc <= 1) 
    {
        printf("No files provided as input.\n");
        return FAILURE;
    }
	
    // Process each file from the argument list in reverse order
    for (int i = argc - 1; i >= 1; i--) 
    {
        // Check if the file name starts with '.' (indicates an invalid file name)
        if (argv[i][0] == '.') 
        {
            printf("File name is missing or starts with an invalid character.\n");
            continue;
        }

        // Check if the file has a valid extension (only '.txt' is allowed)
        char *file_ext = strrchr(argv[i], '.');  // Find the last occurrence of '.'
        if (!file_ext || strcmp(file_ext, ".txt") != 0) 
        {
            printf("%s -> Invalid file extension (only '.txt' allowed).\n", argv[i]);
            continue;
        }

        // Validate if the file exists and can be opened
        if (open_file(argv[i]) == FAILURE) 
        {
            printf("%s -> File does not exist.\n", argv[i]);
            continue;
        }

        // Check if the file is non-empty by determining its size
        if (get_file_size(argv[i]) == FAILURE) 
        {
            printf("%s -> File is empty or cannot be opened.\n", argv[i]);
            continue;
        }

        // Check for duplicate file entries in the linked list
        file_list_t *temp = *head;
        int duplicate = 0;
        while (temp) 
        {
            if (strcmp(temp->file_name, argv[i]) == 0) 
            {
                printf("%s -> Duplicate file.\n", argv[i]);
                duplicate = 1;  // Mark as duplicate
                break;
            }
            temp = temp->filelink;  // Move to the next node
        }
        if (duplicate) 
        {
            continue;  // Skip adding the duplicate file
        }

        // Allocate memory for a new node in the linked list
        file_list_t *new_node = malloc(sizeof(file_list_t));
        if (!new_node) 
        {
            perror("Memory allocation failed.");  // Handle allocation failure
            return FAILURE;
        }

        // Populate the new node with the validated file name
        strcpy(new_node->file_name, argv[i]);
        new_node->filelink = *head;  // Point to the current head of the list
        *head = new_node;  // Update the head to the new node
    }

    // Check if no valid files were added to the linked list
    if (*head == NULL) 
    {
        printf("No valid files were found.\n");
        return FAILURE;
    }

    return SUCCESS;  // Return success if at least one valid file was added
}
