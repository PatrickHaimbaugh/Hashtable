/*
 * Patrick Haimbaugh, hw3.c, CS 24000, Fall 2019
 * Last updated Sept, 2019
 */

// PROVIDED TO STUDENTS

/*DO NOT CHANGE----------BEGIN*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"hashtable.h"

int main() {
    char ch;
    char name[100];
    struct hash_table_element* hash_table = 0;
    int table_size, new_table_size;
    while (1) {
        printf("\nWelcome to Hashtable\n");
        printf("--------------------\n");
        printf("A-Initialize hash table\n");
        printf("B-Compute hash value\n");
        printf("C-Insert name\n");
        printf("D-Load names from file\n");
        printf("E-Delete name\n");
        printf("F-Search name\n");
        printf("G-Number of empty elements\n");
        printf("H-Average list length\n");
        printf("I-Maximum list length\n");
        printf("J-Resize hash table (Extra Credit)\n");
        printf("K-Display hash table\n");
        printf("L-Delete hash table\n");
        printf("M-Exit\n");
        printf("--------------------\n");
        printf("Select an option: ");
        scanf("%c",&ch);
        getchar();
        if (ch != 'M' && ch != 'A' && hash_table == NULL) {
            printf("Initialize hash table first\n");
            exit(0);
        }
        switch (ch) {
            case 'A':
                printf("Input number of hash table elements: ");
                scanf("%d", &table_size);
                getchar();
                hash_table =  init_hash_table(table_size);
                break;
            case 'B':
                printf("Enter the name whose hash value to compute: ");
                scanf("%s", name);
                getchar();        
                printf("hash value: %d\n", get_hash(name, table_size));
                break;
            case 'C':
                printf("Enter the name to insert: "); 
                scanf("%s", name);
                getchar();
                insert_name(hash_table, table_size, name);
                printf("Inserted name: %s\n", name);
                break;
            case 'D':
                printf("Enter the name of the input file: ");
                scanf("%s", name);
                getchar();
                load_from_file(hash_table, table_size, name);
                break;
            case 'E':
                printf("Enter the name to delete: ");
                scanf("%s", name);
                getchar();
                if (delete_name(hash_table, table_size, name)) {
                    printf("Deleted name: %s\n", name);
                }
                else {
                    printf("Name not found: %s\n", name);
                }
                break;
            case 'F':
                printf("Enter the name to search: ");
                scanf("%s", name);
                getchar();
                if (search_in_hash_table(hash_table, table_size, name)) {
                    printf("Found name: %s\n", name);
                }
                else {
                    printf("Name not found: %s\n", name);
                }
                break;
            case 'G':
                printf("Number of empty hash table elements: %d\n",
                    compute_stats_empty(hash_table, table_size));
                break;
            case 'H':
                printf("Average list length: %.2f\n",
                    compute_stats_average(hash_table, table_size));
                break;
            case 'I':
                printf("Length of longest list: %d\n",
                    compute_stats_max(hash_table, table_size));
                break;
            case 'J':
                printf("Enter the new number of hash table elements: ");
                scanf("%d", &new_table_size);
                getchar();
                hash_table = resize_hash_table(hash_table, table_size, new_table_size);
                table_size = new_table_size;
                break;
            case 'K':
                display(hash_table, table_size);
                break;
            case 'L':
                free_hashtable(hash_table, table_size);
                break;
            case 'M':
                exit(0);
            default:
                printf("You have entered wrong option!\n");
                break;
        }
    }
}


void load_from_file(struct hash_table_element* hash_table, int size, char *filename) {
    FILE* fp= fopen(filename,"r");
    assert(fp);
    int num=0;
    fscanf(fp, "%d\n", &num);
    for(int i=0;i<num;i++){
        char name[100];
        fscanf(fp, "%s",name);
        insert_name(hash_table, size, name);
   }
    fclose(fp);
}

void display(struct hash_table_element* hash_table, int table_size) {
    struct sll_node *ptr;
    printf("\nData in Hash Table:\n");
    for (int i = 0; i < table_size; i++) {
        printf("Index %d:", i);
        if (hash_table[i].head == NULL) {
            printf("NULL\n");            
            continue;
        }
        ptr = hash_table[i].head;
        while (ptr != NULL) {
            printf(" %s ->", ptr->name);
            ptr = ptr->next;
        }
        printf(" NULL\n");
    }
}

/*DO NOT CHANGE----END*/
// END PROVIDED TO STUDENTS


// PART 1
struct hash_table_element* init_hash_table(int table_size){

    // write your code here
    struct  hash_table_element * table = (struct hash_table_element *)calloc(table_size, sizeof(struct sll_node *));
    return table; // feel free to modify this line    
    
}

// PART 2
int get_hash(char* name, int table_size) {
    int sum = 0;
    for (int i = 0; i < strlen(name); i++) {
	    sum += name[i];
    }
    // write your code here
    return (sum * sum) % table_size; // feel free to modify this line
    
}

// PART 3
void insert_name(struct hash_table_element* hash_table, 
                 int size, char *name) {

    // write your code here
    struct sll_node * new_node = (struct sll_node *)calloc(1 , sizeof(char *) + sizeof(struct sll_node *));
    //printf("added char pointer -> %ld added sll_node pointer -> %ld\n", sizeof(char *), sizeof(struct sll_node *));
    new_node -> name = (char*)calloc(strlen(name) + 1, sizeof(char));
    //printf("adding string -> %ld\n", sizeof(char) * (strlen(name) + 1));
    strcpy(new_node -> name, name);
    new_node -> next = (hash_table + get_hash(name, size)) -> head;
    (hash_table + get_hash(name, size)) -> head = new_node;
    
}


// PART 4
int delete_name(struct hash_table_element* hash_table, 
                int table_size, char* name) {

    
    // write your code here
    int list_index = get_hash(name, table_size);
    struct sll_node * current_node;
    if ((hash_table + list_index) -> head != NULL) {
        current_node = (hash_table + list_index) -> head;
	if (strcmp(current_node -> name,name) == 0) {
		(hash_table + list_index) -> head = current_node -> next;
		free(current_node -> name);
		free(current_node);
		return 1;
	}
	while(current_node -> next != NULL) {
		if (strcmp(current_node -> next -> name, name) == 0) {
			struct sll_node * intermediate = current_node -> next;
		        current_node -> next = current_node -> next -> next;
			free(intermediate -> name);
			free(intermediate);
	        	return 1;
		} else{
	 	  	current_node = current_node -> next;
		}
	}
    }

    return 0; // feel free to modify this line
    
}

// PART 5
int search_in_hash_table(struct hash_table_element* hash_table, int table_size, char* name) {

    
    // write your code here
    int list_index = get_hash(name, table_size);
    struct sll_node * current_node = (hash_table + list_index) -> head;
    while (current_node != NULL) {
	    if (strcmp(current_node -> name, name) == 0) {
		    return 1;
	    } else {
		    current_node = current_node -> next;
	    }
    }
    return 0; // feel free to modify this line

    
}

// PART 6
int compute_stats_empty(struct hash_table_element* hash_table, int table_size){

    
    // write your code here
    int counter = 0;
    for (int i = 0; i < table_size; i++) {
	    if ((hash_table + i) -> head == NULL) {
		    counter++;
	    }
    }
    return counter; // feel free to modify this line
        
}

// PART 7
float compute_stats_average(struct hash_table_element* hash_table, int table_size){

    
    // write your code here   
    float total = 0;
    for (int i = 0; i < table_size; i++) {
	   struct sll_node * current_node = (hash_table + i) -> head;
	    while (current_node != NULL) {
		   total += 1;
		   current_node = current_node -> next;
            }
    } 
    float average = total / ((float) table_size - (float) compute_stats_empty(hash_table, table_size));
    return average; // feel free to modify this line
    
}

// PART 8
int compute_stats_max(struct hash_table_element* hash_table, int table_size){

    
    // write your code here
    int max = 0;
    for (int i = 0; i < table_size; i++) {
	    int current_length = 0;
	    struct sll_node * current_node = (hash_table + i) -> head;
	    while (current_node != NULL) {
		    current_length++;
		    current_node = current_node -> next;
	    }
	    if (current_length > max) {
		    max = current_length;
	    }
    }
    return max; // feel free to modify this line
        
}


// PART 9
void free_hashtable(struct hash_table_element* hash_table, int table_size){

    // write your code here
   for (int i = 0; i < table_size; i++) {
	  while ((hash_table + i) -> head != NULL) {
	  	  struct sll_node * next = (hash_table + i) -> head -> next;
		if ((hash_table + i) -> head -> name != NULL) {
		   // printf("freeing name at %p\n", (hash_table + i) -> head -> name);
			free((hash_table + i) -> head -> name);
		}
		//printf("freeing node at %p\n", (hash_table + i) -> head);
		free((hash_table + i) -> head);
		(hash_table + i) -> head = next;
	  }
   }
   free(hash_table);
}


// EXTRA CREDIT
struct hash_table_element* resize_hash_table(struct hash_table_element* old_table, int old_size, int new_size){

    
    // write your code here    
    struct hash_table_element * new_table = calloc(new_size, sizeof(char *) + sizeof(struct sll_node *));
    for (int i = 0; i < old_size; i++) {
	    struct sll_node * current_node = (old_table + i) -> head;
	    while (current_node != NULL) {
		    insert_name(new_table, new_size, current_node -> name);
		    struct sll_node * intermediate = current_node;
		    current_node = current_node -> next;
		    delete_name(old_table, old_size, intermediate -> name);
	    }
    }
    free(old_table);
    return new_table; // feel free to modify this line
    
}

