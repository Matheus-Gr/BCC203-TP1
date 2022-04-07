//
// Created by mathe on 3/22/2022.
//

#include "Search.h"

void createPages(int *index_table, int n_pages) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }
    ItemType item;

    for (int i = 0; i < n_pages; ++i) {
        fread(&item, sizeof(item), 1, file);
        index_table[i] = item.key;
        for (int j = 0; j < ITEMSPERPAGE - 1; ++j)
            fread(&item, sizeof(item), 1, file);
    }

    fclose(file);
}

ItemType indexedSequentialAccess(const int *index_table, int key, int n_pages) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < n_pages; ++i) {
//        printf("\n%d < %d\n", key, index_table[i]);
        if (key < index_table[i] || (key > index_table[n_pages - 1] && key < ITEMSPERPAGE * n_pages)) {
            if(key > index_table[i]) i += 1;
            long offset = (long) ((i - 1) * ITEMSPERPAGE * sizeof(ItemType));
            fseek(file, offset, SEEK_SET);
            ItemType item_page[ITEMSPERPAGE];
            fread(&item_page, sizeof(ItemType),
                  ITEMSPERPAGE, file);
            for (int j = 0; j < ITEMSPERPAGE; j++) {
                if (item_page[j].key == key) return item_page[j];
            }
        }
    }
    printf("Key not found!!");
    fclose(file);
    exit(1);
}