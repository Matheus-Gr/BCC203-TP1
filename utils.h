//
// Created by mathe on 3/22/2022.
//

#ifndef TP1_UTILS_H
#define TP1_UTILS_H

#define FILENAME "../file.bin"
#define TRUE 1
#define FALSE 0


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

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



void validateArguments(int argc, int method, int total_items, int order,
                       int key, char *show_result);

char *randString();

void generateFile(char *filename, int total_items, int order);

void readFile(char *filename);

void freeMatrix(ItemType **matrix, int n_pages);

void createTestFile(int method, int total_items, int order,
                    int show_result, int n_test);
#endif //TP1_UTILS_H
