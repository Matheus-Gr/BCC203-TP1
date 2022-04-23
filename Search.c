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

ItemType indexedSearch(const int *index_table, int key, int n_pages) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < n_pages; ++i) {
//        printf("\n%d < %d\n", key, index_table[i]);
        if (key < index_table[i] ||
            (key > index_table[n_pages - 1] && key < ITEMSPERPAGE * n_pages)) {
            if (key > index_table[i]) i += 1;
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

void createBinaryTree() {
    FILE *binaryTree = fopen(BINARYTREEFILE, "wb+");
    if (binaryTree == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

//    BinaryNode bnodeaux;
//    BinaryNode bnodeaux2;
//    ItemType itemaux;
//    fread(&itemaux, sizeof(ItemType),1,file);
//    bnodeaux.pos = 2;
//    bnodeaux.right = 2;
//    bnodeaux.left = 2;
//    bnodeaux.item = itemaux;
//    fwrite(&bnodeaux, sizeof(BinaryNode),1,binaryTree);

    ItemType item;
    BinaryNode child;
    BinaryNode aux;

    int cont = 0;
    int childPos;
    int notEmpty;
    while (fread(&item,sizeof(ItemType), 1, file)) {
        notEmpty = 1;
        child.right = -1;
        child.left = -1;
        child.item = item;
        child.pos = cont;

        fwrite(&child, sizeof(BinaryNode), 1, binaryTree);
        cont++;

        if (cont != 1) {
            rewind(binaryTree);
            childPos = 0;
            while (fread(&aux, sizeof(BinaryNode),
                         1, binaryTree) && notEmpty) {
                if (item.key < aux.item.key)
                    if (aux.left == -1) {
                        aux.left = cont - 1;
                        fseek(binaryTree,
                              (int) (childPos * sizeof(BinaryNode)),
                              SEEK_SET);
                        fwrite(&aux, sizeof(BinaryNode),
                               1, binaryTree);
                        notEmpty = 0;
                    } else {
                        fseek(binaryTree,
                              (int) (aux.left * sizeof(BinaryNode)),
                              SEEK_SET);
                        childPos = aux.left;
                    }
                else {
                    if (aux.right == -1) {
                        aux.right = cont - 1;
                        fseek(binaryTree,
                              (int) (childPos * sizeof(BinaryNode)),
                              SEEK_SET);
                        fwrite(&aux, sizeof(BinaryNode),
                               1, binaryTree);
                        notEmpty = 0;
                    } else {
                        fseek(binaryTree,
                              (int) (aux.right * sizeof(BinaryNode)),
                              SEEK_SET);
                        childPos = aux.right;
                    }
                }
            }
        }
        fseek(binaryTree, 0, SEEK_END);
    }

    fclose(binaryTree);
    fclose(file);
}

ItemType binaryTreeSearch(FILE *binaryTree, int key) {
    BinaryNode nodeAux;
    fread(&nodeAux, sizeof(BinaryNode), 1, binaryTree);
    if (nodeAux.item.key == key) {
        return nodeAux.item;
    } else if (key > nodeAux.item.key && nodeAux.right != -1) {
        fseek(binaryTree,
              (int) (nodeAux.right * sizeof(BinaryNode)),
              SEEK_SET);
        return (binaryTreeSearch(binaryTree, key));
    } else if (key < nodeAux.item.key && nodeAux.left != -1) {
        fseek(binaryTree,
              (int) (nodeAux.left * sizeof(BinaryNode)),
              SEEK_SET);
        return (binaryTreeSearch(binaryTree, key));
    }

    return nodeAux.item;
}