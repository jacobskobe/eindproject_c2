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

int main(int argc, char* argv[]){
    char *path_ptr;
    char path_str[50] = "../json_files/";
    path_ptr = path_str;
    


    // Put all given file data into structs to add to linked list
    for (int i = 1; i < argc; i++){        
        
    
        path_maker(path_ptr, argv[i]);
        
        // check if argument is a json file
        // Make path from file name
        // pass to parse function if argument is json file

        // else skip
        printf("%s\n", path_ptr);
        strcpy(path_ptr, "../json_files/");
    }


    

    free(path_ptr);

}

void path_maker(char *path, char *file_name){
    strcat(path, file_name);
}


