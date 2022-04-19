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

    BinaryNode bnodeaux;
    ItemType itemaux;
    switch (method) {
        case 1:
            createPages(index_table, n_pages);
            item = indexedSearch(index_table, key, n_pages);
            break;

        case 2:
//            fread(&itemaux, sizeof(ItemType),1,file);
//            printf("\nItem:\nkey: %-15d data1: %-15ld data2: %.5s\n",itemaux.key,itemaux.data1,itemaux.data2);
//            bnodeaux.pos = 2;
//            bnodeaux.right = 2;
//            bnodeaux.left = 2;
//            bnodeaux.item = itemaux;
//            fwrite(&bnodeaux, sizeof(BinaryNode),1,binaryTree);
//            fclose(binaryTree);
//            binaryTree = fopen(BINARYTREEFILE, "rb");
//            fread(&bnodeaux, sizeof(ItemType),1,binaryTree);
//            printf("\nItem:\nkey: %-15d data1: %-15ld data2: %.5s\n",bnodeaux.item.key,bnodeaux.item.data1,bnodeaux.item.data2);
            createBinaryTree();
//            FILE *binaryTree = fopen(BINARYTREEFILE, "rb");
//            if (binaryTree == NULL) {
//                printf("Error ao abrir arquivo!\n");
//                exit(1);
//            }
            BinaryNode bnodeaux2;
//            FILE *binaryTree = fopen(BINARYTREEFILE, "rb");
//            fread(&bnodeaux2, sizeof(BinaryNode),1,binaryTree);
//            printf("\nItem:\nkey: %-15d data1: %-15ld data2: %.5s pos: %d\n",
//                   bnodeaux2.item.key, bnodeaux2.item.data1,
//                   bnodeaux2.item.data2, bnodeaux2.pos);
//            fread(nodeAux, sizeof(BinaryNode), 1, binaryTree);
//            printf("%d \n",nodeAux->item.key);
//            fread(nodeAux, sizeof(BinaryNode), 1, binaryTree);
//            printf("%d \n",nodeAux->item.key);
            FILE *binaryTree = fopen(BINARYTREEFILE, "rb");
//            while (fread(&bnodeaux2, sizeof(BinaryNode), 1, binaryTree))
//                printf("--key: %-15d data1: %-15ld data2: %.5s    left: %-5d right: %-5d pos: %-5d\n",
//                       bnodeaux2.item.key, bnodeaux2.item.data1,
//                       bnodeaux2.item.data2,
//                       bnodeaux2.left, bnodeaux2.right, bnodeaux2.pos);
            item = binaryTreeSearch(binaryTree, key);
            break;

        default:
            break;
    }


    printf("\nFounded:\nkey: %-15d data1: %-15ld data2: %.5s\n", item.key,
           item.data1, item.data2);
    return 0;
}
