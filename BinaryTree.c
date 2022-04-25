//
// Created by mathe on 4/24/2022.
//

#include "BinaryTree.h"

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
    ItemType item;
    BinaryNode child;
    BinaryNode aux;

    int cont = 0;
    int childPos;
    int notEmpty;
    while (fread(&item, sizeof(ItemType), 1, file)) {
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