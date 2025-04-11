/*

Name: Niharika
Date: 01-01-2025
Project: Inverted search
Description: An inverted index is an index data structure storing a mapping from content, 
such as words or numbers, to its locations in a database file, or in a document or a set of documents. 
The purpose of an inverted index is to allow fast full text searches, at the cost of increased processing 
when a document is added to the database. The inverted file may be the database file itself, rather than its index. 
It is the most popular data structure used in document retrieval systems, used on a large scale for example in search engines.

*/

#include "Headder.h"

int main(int argc, char *argv[]) 
{
    int db_created = 0, db_updated = 0; 

    file_list_t *file_head = NULL;                                            // Initialize the file list pointer to NULL
    hash_table_t arr[28];                                                    // Array to represent the hash table with 28 entries

    // Initialize hash table
    for (int i = 0; i < 28; i++) 
    {
        arr[i].index = i;                                                   // Assign index to each hash table entry
        arr[i].nodelink = NULL;                                              // Initialize each link to NULL
    }

    // Validate and prepare file list
    if (read_and_validate(argc, argv, &file_head) == SUCCESS) 
    {
        printf("File list validation completed successfully.\n\n");
        print_list(file_head);                                               // Print the validated list of files
    } 
    else 
    {
        printf("Validation of files failed.\n");
        return FAILURE;                                                      // Exit the program if validation fails
    }                                                  

    while (1) 
    {
        // Display menu 
        printf("\n*** MENU OPTIONS ***\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Update Database\n");
        printf("4. Search\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("Please select an option: ");
        int choice;

        // Input validation for menu
        if (scanf("%d", &choice) != 1) 
        {
            printf("Please enter a valid integer.\n");
            __fpurge(stdin);                                                  // Clear invalid input (input buffer)
            continue;                                                         // Prompt the user again
        }

        switch (choice) 
        {
            case 1:
                // Create the database if it has not been created yet
                if (!db_created) 
                {
                    db_created = 1;                                            // Mark database as created
                    if (db_updated) 
                    {                                                           // If database was updated earlier, reset it
                        file_head = NULL;                                      // Reset the file list
                        check_files(arr, argc, argv, &file_head);              // Validate filenames again
                    }
                    // Attempt to create the database
                    if (create_db(&file_head, arr) == SUCCESS) 
                    {
                        printf("Database has been successfully built.\n");
                    } 
                    else 
                    {
                        printf("Unable to build the database.\n");
                    }
                }
                else 
                {
                    printf("Database already exists.\n");
                }
                break;

            case 2:
                // Display the database if it exists
                if (db_created || db_updated) 
                {
                    printf("Displaying the current contents of the database:\n");
                    display_db(arr);                                             // Display the hash table contents
                }
                else 
                {
                    printf("No database available to display.\n");
                }
                break;

            case 3:
            
                // Update the database if it has not been created or updated before
                if (!db_updated && !db_created) 
                {
                    if (update_db(arr, &file_head) == SUCCESS) 
                    {
                        db_updated = 1;                                       // Mark database as updated
                        printf("Database updated successfully.\n");
                    } 
                    else 
                    {
                        printf("Failed to update the database.\n");
                    }
                } 
                else 
                {
                    printf("Database already created/updated, unable to update the database!!\n");
                }
                
                break;

            case 4:
                // Search the database if the data exists
                if (db_updated || db_created) 
                {
                    search_db(arr);                                           // Perform search operation
                    printf("Search operation successful.\n");
                }
                else 
                {
                    printf("Database is empty.\n");
                }
                
                break;

            case 5:
                // Save the database to a file if it exists
                if (db_created || db_updated) 
                {
                    char filename[50];
                    printf("Please enter the filename to export the database (with .txt extension): ");
                    scanf("%s", filename);

                    // Check if the filename has a valid ".txt" extension
                    char *file_ext = strrchr(filename, '.');
                    if (!file_ext || strcmp(file_ext, ".txt") != 0) 
                    {
                        printf("%s -> The file must have a '.txt' extension.\n", filename);
                        printf("Database was not exported.\n");
                    }
                    else
                    {
                        save_db(arr, filename);                                // Save the hash table contents to the file
                        printf("Database has been successfully exported to %s.\n", filename); 
                    }
                } 
                else 
                {
                    printf("No database available for export.\n");
                }
                break;

            case 6:
                // Exit the program
                return SUCCESS;

            default:
                printf("Invalid choice. Please select a valid option from the menu.\n"); // Handle invalid menu choices
        }
    }
    return SUCCESS;
}
