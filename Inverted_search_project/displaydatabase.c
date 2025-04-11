#include"Headder.h"

// Function to display the contents of the hash table
int display_db(hash_table_t  arr[28]) {
    // Print the table header for the database display
    printf("%-8s %-15s %-15s %-15s %-10s\n", "Index", "Word", "Filecount", "Filename", "Wordcount");

    // Iterate through the hash table
    for (int i = 0; i < 28; i++) {
        main_node_t *temp_main = arr[i].nodelink;

        // Traverse all main nodes at the current index
        while (temp_main) {
            // Print the index, word, and file count from the main node
            printf("[%02d]     %-15s %-15d", i, temp_main->word, temp_main->file_count);

            int space = 0;  // Variable to manage alignment for subnodes
            sub_node_t *temp_sub = temp_main->sublink;  // Pointer to traverse subnodes

            // Traverse all subnodes linked to the current main node
            while (temp_sub) {
                // Print the filename and word count of the first subnode on the same line
                if (!space) {
                    space = 1;  // Set space to 1 to handle subsequent subnodes
                    printf("%-15s %-10d", temp_sub->f_name, temp_sub->word_count);
                }
                // For subsequent subnodes, align and print on a new line
                else {
                    printf("\n\t\t\t\t\t%-15s %-10d", temp_sub->f_name, temp_sub->word_count);
                }

                // Move to the next subnode
                temp_sub = temp_sub->slink;
            }

            printf("\n");  // End the current line after processing all subnodes for a main node
            temp_main = temp_main->mainlink;  // Move to the next main node
        }
    }

    return SUCCESS;  // Return SUCCESS after displaying all entries in the hash table
}
