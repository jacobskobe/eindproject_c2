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

int main(int argc, char* argv[]){

    // Put all given file data into structs to add to linked list
    for (int i = 0; i < argc, i++){
        // check if argument is a json file
        // pass to parse function if argument is json file

        // else skip
        
    }



}


// Parse given file into the struct
void item_to_struct_parser(struct Item * item_to_fill, char* file_name) {

}

