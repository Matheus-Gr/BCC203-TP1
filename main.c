#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "Search.h"

int main(int argc, char *argv[]) {
    char *end;
    int method = strtol(argv[1], &end, 10);
    int total_items = strtol(argv[2], &end, 10);
    int order = strtol(argv[3], &end, 10);
    int key = strtol(argv[4], &end, 10);
    char *show_result = argv[5];

    validateArguments(argc, method, total_items, order, key, show_result);

    generateFile(FILENAME, total_items, order);
    if (show_result) readFile(FILENAME);


    ItemType item;
    int n_pages = total_items / ITEMSPERPAGE;
    int index_table[n_pages];

    clock_t begin = clock();


    switch (method) {
        case 1:
            createPages(index_table, n_pages);
            item = indexedSearch(index_table, key, n_pages);
            break;

        case 2:
            createBinaryTree();
            FILE *binaryTree = fopen(BINARYTREEFILE, "rb");
            item = binaryTreeSearch(binaryTree, key);
            break;

        default:
            break;
    }

    clock_t end_time = clock();
    double time_spent = (double)(end_time - begin) / CLOCKS_PER_SEC;

    printf("\nFounded:\nkey: %-15d data1: %-15ld data2: %.5s\n"
           "Execution Time: %.2f", item.key,item.data1, item.data2,time_spent);

    return 0;
}
