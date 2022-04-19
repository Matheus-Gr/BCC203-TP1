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


    ItemType item;
    int n_pages = total_items / ITEMSPERPAGE;
    int index_table[n_pages];
    switch (method) {
        case 1:
                createPages(index_table,n_pages);
                item = indexedSearch(index_table, key, n_pages);
            break;

        case 2:
            createBinaryTree();
            FILE *binaryTree = fopen(BINARYTREEFILE, "rb");
            if (binaryTree == NULL) {
                printf("Error ao abrir arquivo!\n");
                exit(1);
            }
            BinaryNode *nodeAux;
            fread(nodeAux, sizeof(BinaryNode), 1, binaryTree);
            printf("%d \n",nodeAux->item.key);
            fread(nodeAux, sizeof(BinaryNode), 1, binaryTree);
            printf("%d \n",nodeAux->item.key);
            fread(nodeAux, sizeof(BinaryNode), 1, binaryTree);
            printf("%d \n",nodeAux->item.key);
            item = binaryTreeSearch(binaryTree,NULL,key);
            break;

        default:
            break;
    }




    printf("\nFounded:\nkey: %-15d data1: %-15ld data2: %.5s\n",item.key,item.data1,item.data2);
    return 0;
}
