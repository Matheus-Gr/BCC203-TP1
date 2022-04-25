//
// Created by mathe on 3/22/2022.
//

#ifndef TP1_UTILS_H
#define TP1_UTILS_H

//Arquivo que será utilizado para criação dos registros e busca em alguns casos
#define FILENAME "../file.bin"
//Variaveis que serão utilizadas como booleanas
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

/* Estrutura responsavel por definir os registros
 *
 * key = Guardara a chave que será essencial para indentificar o registro e
 * consequentemente achalo quando uma busca for acionada
 * data1 = Reponsavel por guardar um numero gerado aleatoriamente
 * data2 = Reponsavel por guardar uma string de 5000 caracteres geradas
 * aleatoriamente
 */
typedef struct {
    int key;
    long int data1;
    char data2[5000];
} ItemType;

//DESCRIÇÃO DAS FUNÇÕES NO ARQUIVO .C CORRESPONDENTE
void validateArguments(int argc, int method, int total_items, int order,
                       int key, char *show_result);

char *randString();

void generateFile(int total_items, int order);

void readFile(char *filename);

#endif //TP1_UTILS_H
