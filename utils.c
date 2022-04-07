//
// Created by mathe on 3/22/2022.
//

#include "utils.h"



void validateArguments(int argc, int method, int total_items, int order,
                       int key, char *show_result) {
    if (argc < 2) {
        printf("Must pass at least 4 arguments,"
               " <method> <total_items> <order> <key>");
        exit(1);
    } else if (method < 1 || method > 4) {
        printf("method must be between 1 and 4");
        exit(1);
    } else if (total_items == 0) {
        printf("total_items must be different from 0");
        exit(1);
    } else if (order < 1 || order > 3) {
        printf("order must be between 1 and 3");
        exit(1);
    } else if (key < 0) {
        printf("Invalid key, must be positive integer");
        exit(1);
    } else if (show_result != NULL && strcmp("-P", show_result) != 0) {
        printf("Invalid optional parameter %s", show_result);
        exit(1);
    }
}

char* randString() {
    char nullStr[] = "";
    char *text = (char*) malloc(5001 * sizeof(char));
    strcpy(text,nullStr);

    char current_char;
    char str_base[] = "0123456789"
                      "abcdefghijklmnopqrstuvwxyz"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 5000; ++i) {
        current_char = str_base[rand() % (sizeof (str_base) - 1)];
        strncat(text, &current_char, 1);
    }
    return text;
}

void generateFile(char* filename, int total_items, int order) {
    FILE *file = fopen(filename, "wb");

    ItemType item;
    srand(time(NULL));

    int random_array[total_items];

    int duplicated = 0;

    switch (order) {
        case 1:
            for (int i = 0; i < total_items; ++i) {
                item.key = i + 1;
                item.data1 = rand() % LONG_MAX;
                char* text = randString();
                strcpy(item.data2, text);
                fwrite(&item, sizeof(ItemType) , 1, file);
            }
            break;

        case 2:
            for (int i = total_items; i > 0; --i) {
                item.key = i;
                item.data1 = rand() % LONG_MAX;
                char* text = randString();
                strcpy(item.data2, text);
                fwrite(&item, sizeof(ItemType) , 1, file);
            }
            break;

        case 3:
            for (int i = 0; i < total_items; ++i) random_array[i] = -1;

            for (int i = 0; i < total_items; ++i) {
                do {
                    item.key = rand() % total_items + 1;
                    random_array[i] = item.key;
                    int occurancy = 0;
                    for (int j = 0; j < total_items; ++j) {
                        if(random_array[j] == item.key) occurancy ++;
                    }
                    duplicated = occurancy > 1 ? 1 : 0;
                } while (duplicated);

                item.data1 = rand() % LONG_MAX;
                char* text = randString();
                strcpy(item.data2, text);
                fwrite(&item, sizeof(ItemType) , 1, file);
            }
            break;

    }

//    free(item.data2);
    fclose(file);
}

void readFile(char* filename){
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }
    ItemType item;

    while (fread(&item, sizeof(ItemType), 1, file))
        printf("key: %-15d data1: %-15ld data2: %.5s\n",
               item.key,item.data1,item.data2);
    fclose(file);
}

void freeMatrix(ItemType** matrix, int n_pages){
    for (int i = 0; i < n_pages; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}


