#include "Headder.h"

// Function to save the database to a specified file
void save_db(hash_table_t arr[28], const char *filename) 
{
    printf("Saving database to %s...\n", filename);

    // Open the specified file in write mode
    FILE *db_file = fopen(filename, "w");
    if (!db_file) 
    {
        perror("Unable to open file for saving\n");  // If file cannot be opened, print an error
        return;  // Exit the function
    }

    // Loop through each index (bucket) of the hash table
    for (int i = 0; i < 28; i++) 
    {
        main_node_t *temp_main = arr[i].nodelink;  // Pointer to the first main node in the list at index 'i'

        // Traverse through all the main nodes in the current hash bucket
        while (temp_main) 
        {
            // Write the main node's data (index, word, file count) to the file
            fprintf(db_file, "#%d;%s;%d;", i, temp_main->word, temp_main->file_count);

            sub_node_t *temp_sub = temp_main->sublink;  // Pointer to the first subnode for the current main node

            // Iterate through all subnodes related to the current main node
            while (temp_sub) 
            {
                // Write the subnode's data (file name and word count) to the file
                fprintf(db_file, "%s;%d;", temp_sub->f_name, temp_sub->word_count);
                temp_sub = temp_sub->slink;  // Move to the next subnode in the list
            }

            // After processing all subnodes, mark the end of the current main node's data block
            fprintf(db_file, "#\n");

            // Move to the next main node in the list for the current bucket
            temp_main = temp_main->mainlink;
        }
    }

    // Close the file after writing all data to ensure data is saved correctly
    fclose(db_file);

    // Inform the user that the database has been saved successfully
    printf("Database successfully saved to %s.\n", filename);
}
