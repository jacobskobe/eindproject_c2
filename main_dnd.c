#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


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

int main(int argc, char* argv[]){

    char *path_ptr;
    char path_str[50] = "../json_files/";
    path_ptr = path_str;
    


    // Put all given file data into structs to add to linked list
    for (int i = 1; i < argc; i++){        
        
        // check if argument is a json file
        if (check_extension(argv[i]) == 0) {
            // make path from cmd argument and path_str to check for file to parse
            path_maker(path_ptr, argv[i]);
            printf("%s\n", path_ptr);
        }
        else {
            continue;
        }
        // pass to parse function if argument is json file

        // else skip

        // sets value of path_str back to original to check for new file
        strcpy(path_ptr, "../json_files/");
    }

    free(path_ptr);

}

void path_maker(char *path, char *file_name){
    strcat(path, file_name);
}

int check_extension(char *file_name){

    char *return_extension;
    return_extension = strrchr(file_name, '.');

    if (strcmp(return_extension, ".json") == 0) {
        return 0;
    }
    else {
        return 1;
    }

}


