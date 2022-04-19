//
// Created by mathe on 3/22/2022.
//

#ifndef TP1_UTILS_H
#define TP1_UTILS_H

#define FILENAME "../file.bin"
#define BINARYTREEFILE "../binaryTree.bin"
#define ITEMSPERPAGE 20
#define ORDERM 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int key;
    long int data1;
    char data2[5000];
} ItemType;

typedef struct {
    int left;
    int right;
    ItemType item;
    int pos;
} BinaryNode;

typedef struct PageType* PointerType;

typedef struct {
    short n_items;
    ItemType items[ORDERM];
    PointerType pointers[ORDERM + 1];
} PageType;

void validateArguments(int argc, int method, int total_items, int order,
                       int key, char *show_result);

char *randString();

void generateFile(char *filename, int total_items, int order);

void readFile(char *filename);

void freeMatrix(ItemType **matrix, int n_pages);

#endif //TP1_UTILS_H
