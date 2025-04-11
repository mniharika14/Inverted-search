#include "Headder.h"

// Function to check filenames in the hash table and add missing files to the flist
void check_files(hash_table_t arr[28], int argc, char *argv[], file_list_t **f_head) 
{
    if (argc < 2) 
    {
        printf("No filenames provided in the command-line arguments.\n");
        return;
    }

    // Iterate over each filename provided in the command-line arguments
    for (int i = 1; i < argc; i++) 
    {
        char *filename_to_check = argv[i];
        int found = 0;

        // Traverse the hash table to check if the filename already exists
        for (int index = 0; index < 28; index++) {
            main_node_t *main_node = arr[index].nodelink;

            // Traverse the main nodes at this index
            while (main_node != NULL) {
                sub_node_t *sub_node = main_node->sublink;

                // Traverse the sub-nodes of the main node
                while (sub_node != NULL) {
                    if (strcmp(sub_node->f_name, filename_to_check) == 0) {
                        printf("Filename '%s' found in hash table at index %d.\n", filename_to_check, index);
                        found = 1;
                        break;
                    }
                    sub_node = sub_node->slink;
                }

                if (found) {
                    break;
                }

                main_node = main_node->mainlink;
            }

            if (found) {
                break;
            }
        }

        // If the filename was not found
        if (!found) {
            printf("Filename '%s' not found in the hash table. Adding to file list.\n", filename_to_check);

            // Add the filename to the flist
            file_list_t *new_file = malloc(sizeof(file_list_t));
            if (new_file == NULL) {
                printf("Memory allocation failed for new file.\n");
                return; // Return early to avoid further errors
            }

            // Initialize the new node
            strcpy(new_file->file_name, filename_to_check);
            new_file->filelink = NULL;

            // Insert at the front of the list
            if (*f_head == NULL) {
                *f_head = new_file;
            } else {
                new_file->filelink = *f_head;
                *f_head = new_file;
            }
        }
    }
}
