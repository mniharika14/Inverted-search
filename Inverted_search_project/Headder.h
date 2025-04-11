#ifndef HEADDER_H
#define HEADDER_H

#define SUCCESS 0
#define FAILURE -1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

// Data Structure for Hash Table 
typedef struct Hashtable {
    int index;
    struct main_node *nodelink;
} hash_table_t;

// Structure for File List 
typedef struct file_list {
    char file_name[50];
    struct file_list *filelink;
} file_list_t;

// Structure for Main Node 
typedef struct main_node {
    char word[30];
    int file_count;
    struct main_node *mainlink;
    struct sub_node *sublink;
} main_node_t;

// Structure for Sub Node 
typedef struct sub_node {
    char f_name[30];
    int word_count;
    struct sub_node *slink;
} sub_node_t;

// Function Prototypes
int read_and_validate(int argc, char *argv[], file_list_t **head);
int print_list(file_list_t *head);
int open_file(char *filename);
void insert_file(file_list_t **f_head, const char *file_name);
void check_files(hash_table_t arr[28], int argc, char *argv[], file_list_t **f_head);
int get_file_size(char *filename);
int create_db(file_list_t **head, hash_table_t arr[28]);
int display_db(hash_table_t arr[28]);
void save_db(hash_table_t arr[28], const char *filename);
int update_db(hash_table_t arr[28], file_list_t **f_head);
int search_db(hash_table_t arr[28]);

#endif