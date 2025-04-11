#include "Headder.h"

// Function to create a database with the files passed as command line arguments
int create_db(file_list_t **head, hash_table_t arr[28]) 
{
    char word[30]; // Buffer to store each word read from the file
    file_list_t *temp = *head; // Pointer to traverse the file list
    int index; // Index to categorize the word based on its starting character

    while (temp) 
    {
        // Opening the current file in read mode
        FILE *fptr = fopen(temp->file_name, "r");
        if (!fptr) 
        {
            // If file cannot be opened, display an error and move to the next file
            printf("%s file doesn't exist\n", temp->file_name);
            temp = temp->filelink;
            continue;
        }

        // Reading words from the file until the end of file is reached
        while (fscanf(fptr, "%s", word) != EOF) 
        {
            // Generating the index to categorize the word
            char ch = word[0];
            if (ch >= 'A' && ch <= 'Z') 
            {
                index = ch - 'A'; // Index for uppercase letters
            } 
            else if (ch >= 'a' && ch <= 'z') 
            {
                index = ch - 'a'; // Index for lowercase letters
            } 
            else if (ch >= '0' && ch <= '9') 
            {
                index = 26; // Index for digits
            } 
            else 
            {
                index = 27; // Index for special characters
            }

            // Traversing the main node list for the calculated index
            main_node_t *main_temp = arr[index].nodelink;
            main_node_t *main_prev = NULL;

            // Searching for the word in the main node list
            while (main_temp) 
            {
                if (strcmp(main_temp->word, word) == 0) 
                {
                    // If word is found, traverse the sub-node list
                    sub_node_t *sub_temp = main_temp->sublink;
                    sub_node_t *sub_prev = NULL;

                    // Searching for the file in the sub-node list
                    while (sub_temp) {
                        if (strcmp(sub_temp->f_name, temp->file_name) == 0) 
                        {
                            // If file is found, increment the word count
                            sub_temp->word_count++;
                            break;
                        }
                        sub_prev = sub_temp;
                        sub_temp = sub_temp->slink;
                    }

                    if (!sub_temp) 
                    {
                        // If file is not found, create a new sub-node
                        sub_node_t *new_sub = malloc(sizeof(sub_node_t));
                        if (!new_sub) 
                        {
                            perror("Memory allocation failed");
                            return FAILURE;
                        }
                        strcpy(new_sub->f_name, temp->file_name); // Assign file name
                        new_sub->word_count = 1; // Initialize word count to 1
                        new_sub->slink = NULL; // No further links

                        if (sub_prev) 
                        {
                            sub_prev->slink = new_sub; // Link the new sub-node
                        } 
                        else 
                        {
                            main_temp->sublink = new_sub; // Update sublink of the main node
                        }

                        // Increment file count in the main node
                        main_temp->file_count++;
                    }
                    break;
                }
                main_prev = main_temp;
                main_temp = main_temp->mainlink;
            }

            if (!main_temp) 
            {
                // If word is not found, create a new main node
                main_node_t *new_main = malloc(sizeof(main_node_t));
                if (!new_main) 
                {
                    perror("Memory allocation failed");
                    return FAILURE;
                }
                strcpy(new_main->word, word); // Assign the word
                new_main->file_count = 1; // Initialize file count to 1
                new_main->mainlink = NULL; // No further links
                new_main->sublink = NULL; // No sub-nodes initially

                if (main_prev) 
                {
                    main_prev->mainlink = new_main; // Link the new main node
                } 
                else 
                {
                    arr[index].nodelink = new_main; // Update the hash table
                }

                // Create a new sub-node for the file
                sub_node_t *new_sub = malloc(sizeof(sub_node_t));
                if (!new_sub) 
                {
                    perror("Memory allocation failed");
                    return FAILURE;
                }
                strcpy(new_sub->f_name, temp->file_name); // Assign file name
                new_sub->word_count = 1; // Initialize word count to 1
                new_sub->slink = NULL; // No further links
                new_main->sublink = new_sub; // Link the sub-node to the main node
            }
        }
        fclose(fptr); // Close the current file
        temp = temp->filelink; // Move to the next file in the list
    }
    return SUCCESS; // Return success after processing all files
}

