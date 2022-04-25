//
// Created by mathe on 4/24/2022.
//

#include "Indexed.h"

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

ItemType indexedSearch(const int *index_table,
                       int key, int n_pages,int total_items) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < n_pages; ++i) {
//        printf("\n%d < %d || ( %d >= %d && %d <= %d)\n",
//               key, index_table[i], key, index_table[n_pages - 1],
//               key, total_items);
        if (key < index_table[i] ||
            (key >= index_table[n_pages - 1] && key <= total_items)) {
            int aux = i - 1;
            if (key >= index_table[n_pages - 1]) aux = i + 1;
            long offset = (long) ((aux) * ITEMSPERPAGE * sizeof(ItemType));
            fseek(file, offset, SEEK_SET);
            ItemType item_page[ITEMSPERPAGE];
            fread(&item_page, sizeof(ItemType),
                  ITEMSPERPAGE, file);
            for (int j = 0; j < ITEMSPERPAGE; j++) {
//                printf("%d == %d \n_items",item_page[j].key, key);
                if (item_page[j].key == key) return item_page[j];
            }
        }
    }
    printf("Key %d not found!!",key);
    fclose(file);
    exit(1);
}