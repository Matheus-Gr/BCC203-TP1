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

    generateFile(FILENAME,total_items, order);
    if(show_result) readFile(FILENAME);

    int n_pages = total_items / ITEMSPERPAGE;
    int index_table[n_pages];
    createPages(index_table,n_pages);
    ItemType item = indexedSequentialAccess(index_table, key, n_pages);

    printf("\nFounded:\nkey: %-15d data1: %-15ld data2: %.5s\n",item.key,item.data1,item.data2);
    return 0;
}
