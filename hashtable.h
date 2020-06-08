#ifndef HASHTABLE_H
#define HASHTABLE_H

struct sll_node {
    char* name;
    struct sll_node *next;
};

struct hash_table_element {
    struct sll_node *head;
};

struct hash_table_element* init_hash_table(int table_size);

int get_hash(char* name, int table_size);

void insert_name(struct hash_table_element* hash_table, int table_size, char *name);

void load_from_file(struct hash_table_element* hash_table, int table_size, char *name);

int delete_name(struct hash_table_element* hash_table, int table_size, char* name);

int search_in_hash_table(struct hash_table_element* hash_table, int table_size, char* name);

void display(struct hash_table_element* hash_table, int table_size);

int compute_stats_empty(struct hash_table_element* hash_table, int table_size);

float compute_stats_average(struct hash_table_element* hash_table, int table_size);

int compute_stats_max(struct hash_table_element* hash_table, int table_size);

struct hash_table_element* resize_hash_table(struct hash_table_element* old_table, int old_size, int new_size);

void free_hashtable(struct hash_table_element* hash_table, int table_size);

#endif // HASHTABLE_H
