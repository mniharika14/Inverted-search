#include "Headder.h"

// Function to search the database only if it's already created
int search_db(hash_table_t arr[28]) 
{
    char data[50];
    // Reading word from the user
    printf("Enter the word you want to search: ");
    scanf("%s", data);

    int index;
    // Getting the first character of the word to generate the index
    char ch = data[0];
    if (ch >= 'A' && ch <= 'Z') 
    {
        index = ch - 'A';  // Map uppercase letters to indices 0-25
    } 
    else if (ch >= 'a' && ch <= 'z') 
    {
        index = ch - 'a';  // Map lowercase letters to indices 0-25
    } 
    else if (ch >= '0' && ch <= '9') 
    {
        index = 26;  // Map digits to index 26
    } 
    else 
    {
        index = 27;  // Map other characters to index 27
    }

    // Check if the linked list at the given index exists
    if (arr[index].nodelink) 
    {
        main_node_t *main_temp = arr[index].nodelink;  // Pointer to the main node list at this index

        // Traverse through main nodes in the hash table bucket
        while (main_temp) 
        {
            // Check if the word matches the main node data
            if (strcmp(main_temp->word, data) == 0) 
            {
                printf("Word '%s' is present in %d file(s)\n", data, main_temp->file_count);

                sub_node_t *sub_temp = main_temp->sublink;  // Pointer to the subnode list for the found word
                // Traverse through subnodes to print file details and word counts
                while (sub_temp) 
                {
                    printf("In file: %s - %d time(s)\n", sub_temp->f_name, sub_temp->word_count);
                    sub_temp = sub_temp->slink;  // Move to the next subnode
                }
                return SUCCESS;  // Successfully found the word in the database
            }
            main_temp = main_temp->mainlink;  // Move to the next main node
        }
    }

    // If the word is not found in the database
    printf("Word '%s' is not found.\n", data);
    return FAILURE;  // Word not found
}

