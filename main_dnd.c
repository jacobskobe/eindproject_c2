#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include "cJSON.h"

// Linked list struct
struct item_list {
    struct Item *item_dnd;
    struct item_list *next_item;
};

// dnd object struct
struct Item {
    char *name;
    int weight;
    struct item_cost {
        int cost;
        char *cost_unit;
    } cost;
    char *description;
};

void path_maker(char *path, const char *file_name);
int check_extension(const char *file_name);
int check_file_exist(const char *file_path);
void push_to_list(struct item_list **head, struct Item *object_to_push);
void fill_item_from_json(struct Item *item, const char *filename);
char *read_file(const char *filename);
cJSON *parse_json(const char *json_data);
void extract_item(const cJSON *json, struct Item *item);

int main(int argc, char* argv[]) {

    // make first linked list object
    struct item_list *head = NULL;

    // counter to check for the first item to add to list
    int counter_list = 0;

    char path_str[256] = "C:\\Users\\kobej\\Desktop\\skorro23_24\\C2\\Eindproject_KobeJacobs\\json_files\\";
    char *path_ptr = path_str;

    // Put all given file data into structs to add to linked list
    for (int i = 1; i < argc; i++) {        
        // check if argument is a json file
        if (check_extension(argv[i]) == 0) {
            // make path from cmd argument and path_str to check for file to parse
            path_maker(path_ptr, argv[i]);

            // Check if file exists
            if (check_file_exist(path_ptr) == 0) {

                // Allocate memory for new Item and fill it with data from JSON file
                struct Item *new_item = (struct Item *)malloc(sizeof(struct Item));
                fill_item_from_json(new_item, path_ptr);
                
                if (counter_list == 0) {
                    // create first node for linked list
                    head = (struct item_list *)malloc(sizeof(struct item_list));
                    head->item_dnd = new_item;
                    head->next_item = NULL;
                    counter_list++;
                } else {
                    // Make new object to add to the linked list (push)
                    push_to_list(&head, new_item);
                }
            } else {
                // File does not exist
                continue;
            }
        } else {
            continue;
        }
        // sets value of path_str back to original to check for new file
        strcpy(path_ptr, "C:\\Users\\kobej\\Desktop\\skorro23_24\\C2\\Eindproject_KobeJacobs\\json_files\\");
    }

    // Print and free the linked list
    struct item_list *current = head;
    while (current != NULL) {
        printf("Name: %s\n", current->item_dnd->name);
        printf("Weight: %d\n", current->item_dnd->weight);
        printf("Cost: %d %s\n", current->item_dnd->cost.cost, current->item_dnd->cost.cost_unit);
        printf("Description: %s\n\n", current->item_dnd->description);
        struct item_list *temp = current;
        current = current->next_item;
        free(temp->item_dnd->name);
        free(temp->item_dnd->cost.cost_unit);
        free(temp->item_dnd->description);
        free(temp->item_dnd);
        free(temp);
    }

    return 0;
}

// Function to concatenate file name to path
void path_maker(char *path, const char *file_name) {
    strcat(path, file_name);
}

// Function to check if file has .json extension
int check_extension(const char *file_name) {
    const char *extension = strrchr(file_name, '.');
    return (extension != NULL && strcmp(extension, ".json") == 0) ? 0 : 1;
}

// Function to check if file exists
int check_file_exist(const char *file_path) {
    struct stat buffer;
    return (stat(file_path, &buffer) == 0) ? 0 : 1;
}

// Function to push new item to linked list
void push_to_list(struct item_list **head, struct Item *object_to_push) {
    struct item_list *new_item = (struct item_list *)malloc(sizeof(struct item_list));
    new_item->item_dnd = object_to_push;
    new_item->next_item = NULL;

    if (*head == NULL) {
        *head = new_item;
    } else {
        struct item_list *current = *head;
        while (current->next_item != NULL) {
            current = current->next_item;
        }
        current->next_item = new_item;
    }
}

// Function to read the entire JSON file into a string
char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(length + 1);
    if (!data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);
    return data;
}

// Function to parse JSON data from a string
cJSON *parse_json(const char *json_data) {
    cJSON *json = cJSON_Parse(json_data);
    if (!json) {
        fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
    }
    return json;
}

// Function to extract values from the JSON object and fill the Item struct
void extract_item(const cJSON *json, struct Item *item) {
    const cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    const cJSON *weight = cJSON_GetObjectItemCaseSensitive(json, "weight");
    const cJSON *quantity = cJSON_GetObjectItemCaseSensitive(json, "quantity");
    const cJSON *cost_unit = cJSON_GetObjectItemCaseSensitive(json, "unit");
    const cJSON *description = cJSON_GetObjectItemCaseSensitive(json, "description");

    // Check and assign name
    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        item->name = strdup(name->valuestring);
    } else {
        item->name = strdup("N/A");
    }

    // Check and assign weight
    if (cJSON_IsNumber(weight)) {
        item->weight = weight->valueint;
    } else {
        item->weight = 0;  // Default value
    }

    // Check and assign cost
    if (cJSON_IsNumber(quantity)) {
        item->cost.cost = quantity->valueint;
    } else {
        item->cost.cost = 0;  // Default value
    }

    // Check and assign cost unit
    if (cJSON_IsString(cost_unit) && (cost_unit->valuestring != NULL)) {
        item->cost.cost_unit = strdup(cost_unit->valuestring);
    } else {
        item->cost.cost_unit = strdup("N/A");
    }

    // Check and assign description
    if (cJSON_IsString(description) && (description->valuestring != NULL)) {
        item->description = strdup(description->valuestring);
    } else {
        item->description = strdup("N/A");
    }
}

// Function to fill the Item struct with data from a JSON file
void fill_item_from_json(struct Item *item, const char *filename) {
    char *json_data = read_file(filename);
    if (!json_data) {
        return;
    }

    cJSON *json = parse_json(json_data);
    if (!json) {
        free(json_data);
        return;
    }

    extract_item(json, item);

    cJSON_Delete(json);
    free(json_data);
}
