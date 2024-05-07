#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>


// Linked list struct
struct item_list {
    struct Item *item_dnd;
    struct item_list *next_item;
};

// dnd object struct
struct Item {

    char name;
    int weight;
    struct item_cost {
        int cost;
        char cost_unit[2];
    };
    char weapon_category;
    char description;

};


void path_maker(char *path, char *file_name);
int check_extension(char *file_name);
int check_file_exist(char *file_path);
void push_to_list(struct item_list **head, struct Item *object_to_push);

int main(int argc, char* argv[]){

    // make first linked list object
    struct item_list *head = NULL;
    head = (struct item_list *) malloc(sizeof(struct item_list));
    head->item_dnd = (struct Item*) malloc(sizeof(struct Item));
    head->next_item = NULL;

    // counter to check for the first item to add to list
    int counter_list = 0;

    char *path_ptr;
    char path_str[100] = "C:\\Users\\kobej\\Desktop\\skorro23_24\\C2\\Eindproject_KobeJacobs\\json_files\\";
    path_ptr = path_str;

    // Array for data from parsed file
    char *data_from_file[6];
    


    // Put all given file data into structs to add to linked list
    for (int i = 1; i < argc; i++){        
        
        // check if argument is a json file
        if (check_extension(argv[i]) == 0) {
            // make path from cmd argument and path_str to check for file to parse
            path_maker(path_ptr, argv[i]);
            printf("%s\n", path_ptr);

            // Check if file exists
            if (check_file_exist(path_ptr)){
                // File does not exists
                
            }
            else {
                // File exists
                printf("%d\n", check_file_exist(path_ptr));
                continue;

                // Make new node for 
                if (counter_list == 0){
                    // create first node for linked list
                    continue;
                }
                else {
                    continue;
                }
            }
            
        }
        else {
            continue;
        }
        // pass to parse function if argument is json file

        // else skip

        // sets value of path_str back to original to check for new file
        strcpy(path_ptr, "C:\\Users\\kobej\\Desktop\\skorro23_24\\C2\\Eindproject_KobeJacobs\\json_files\\");
    }

    free(path_ptr);

}

void path_maker(char *path, char *file_name){
    strcat(path, file_name);
}

int check_extension(char *file_name){

    char *return_extension;
    // save string starting at the '.' char
    return_extension = strrchr(file_name, '.');

    // check if string is the right extension format
    if (strcmp(return_extension, ".json") == 0) {
        return 0;
    }
    else {
        return 1;
    }

}

int check_file_exist(char *file_path){
    FILE *file;
    file = fopen(file_path, "r");

    if (file != NULL){
        fclose(file);
        return 0;
    }
    else {
        return 1;
    }
}

void push_to_list(struct item_list **head, struct Item *object_to_push){
    // Create new object
    struct item_list *new_item;
    // Allocate memory for new linked list object
    new_item = (struct item_list *) malloc(sizeof(struct item_list));
    // Allocate memory for new Item
    new_item->item_dnd = (struct Item *) malloc(sizeof(struct Item));
    new_item->next_item = NULL;

    if (*head == NULL){
        *head = new_item;
    }
    else {
        struct item_list *current = *head;
        while(current->next_item != NULL){
            current = current->next_item;
        }
        current->next_item = new_item;
    }

}


void fill_first_item(struct Item *item_to_fill, FILE *file){



}

