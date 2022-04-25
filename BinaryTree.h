//
// Created by mathe on 4/24/2022.
//

#ifndef TP1_BINARYTREE_H
#define TP1_BINARYTREE_H

#include "utils.h"
#define BINARYTREEFILE "../binaryTree.bin"

void createBinaryTree();

ItemType binaryTreeSearch(FILE *binaryTree, int key);

#endif //TP1_BINARYTREE_H
