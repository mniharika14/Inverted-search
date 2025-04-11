
#include "Headder.h"

int update_db(hash_table_t arr[28], file_list_t **f_head) 
{
    char newfile[100];
    printf("Enter the file name to update: ");
    scanf("%s", newfile);

    // Check if the file has a '.txt' extension
    char *ext = strrchr(newfile, '.');
    if (!ext || strcmp(ext, ".txt") != 0) 
    {
        printf("%s -> File should have '.txt' extension only.\n", newfile);
        return FAILURE;
    }

    // Open the file in read mode
    FILE *fptr = fopen(newfile, "r");
    if (fptr == NULL) 
    {
        printf("%s File doesn't exist.\n", newfile);
        return FAILURE;
    }

    // Validate the first character of the file
    char first_char = fgetc(fptr);
    if (first_char != '#') 
    {
        printf("File must start with '#' character.\n");
        fclose(fptr);
        return FAILURE;
    }
    rewind(fptr);

    char line[256];
    // Read each line from the file
    while (fgets(line, sizeof(line), fptr) != NULL) 
    {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';

        // Validate the format of the line (must start and end with '#')
        if (line[0] != '#' || line[strlen(line) - 1] != '#') 
        {
            printf("Invalid format. Each line must start and end with '#'.\n");
            fclose(fptr);
            return FAILURE;
        }

        // Tokenize the line to extract the index
        char *token = strtok(line + 1, ";"); // Skip the initial '#'
        if (!token) {
            printf("Missing index field.\n");
            return FAILURE;
        }
             int index = atoi(token);

        // Tokenize the line to extract the word
        token = strtok(NULL, ";");
        if (!token) {
            printf("Missing word field.\n");
            return FAILURE;
        }
        char word[50];
        strcpy(word, token);

        // Tokenize the line to extract the file count
        token = strtok(NULL, ";");
        if (!token) {
            printf("Missing file count field.\n");
            return FAILURE;
        }
        int file_count = atoi(token);
        if (file_count <= 0) {
            printf("Invalid file count %d. File count can't be negative\n", file_count);
            return FAILURE;
        }

        // Allocate memory for a new main node
        main_node_t *m_new = malloc(sizeof(main_node_t));
        if (!m_new) {
            printf("Memory allocation failed.\n");
            fclose(fptr);
            return FAILURE;
        }
        strcpy(m_new->word, word);  // Store the word in the main node
        m_new->file_count = file_count;  // Store the file count in the main node
        m_new->mainlink = NULL;  // Initialize mainlink to NULL
        //m_new->sublink = NULL;  // Initialize sublink to NULL (not needed at this point)

        // Parse the sub-nodes for the file and word counts
        sub_node_t *prev = NULL;
        for (int i = 0; i < file_count; i++) {
            token = strtok(NULL, ";");
            if (!token) {
                printf("Missing filename for sub-node.\n");
                free(m_new);
                return FAILURE;
            }
            char filename[50];
            strcpy(filename, token);

            token = strtok(NULL, ";");
            if (!token) {
                printf("Missing word count for sub-node.\n");
                free(m_new);
                return FAILURE;
            }
            int word_count = atoi( token );

            // Allocate memory for a new sub-node
            sub_node_t *s_new = malloc(sizeof(sub_node_t));
            if (!s_new) {
                printf("Memory allocation failed for sub-node.\n");
                free(m_new);
                fclose(fptr);
                return FAILURE;
            }
            strcpy(s_new->f_name, filename);  // Store the filename in the sub-node
            s_new->word_count = word_count;  // Store the word count in the sub-node
            s_new->slink = NULL;  // Initialize slink to NULL

            // Link sub-node to the main node
            if (!prev) {
                m_new->sublink = s_new;  // If it's the first sub-node, link it directly
            } else {
                prev->slink = s_new;  // Otherwise, link it to the previous sub-node
            }
            prev = s_new;  // Update the previous sub-node
        }

        // Add the main node to the hash table
        if (!arr[index].nodelink) {
            arr[index].nodelink = m_new;  // If no node exists at the index, add the new main node
        } else {
            main_node_t *temp = arr[index].nodelink;
            while (temp->mainlink) {
                temp = temp->mainlink;  // Traverse to the end of the list
            }
            temp->mainlink = m_new;  // Link the new main node at the end of the list
        }
    }

    // Validate the last character of the file
    fseek(fptr, -2, SEEK_END);
    char last_char = fgetc(fptr);
    if (last_char != '#') {
        printf("File must end with '#' character.\n");
        fclose(fptr);
        return FAILURE;
    }

    fclose(fptr);  // Close the file
    return SUCCESS;  // Return success
}
