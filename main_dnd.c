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

int main(int argc, char* argv[]){

    char *path_ptr;
    char path_str[100] = "C:\\Users\\kobej\\Desktop\\skorro23_24\\C2\\Eindproject_KobeJacobs\\json_files\\";
    path_ptr = path_str;
    


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


