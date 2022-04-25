//
// Created by mathe on 4/24/2022.
//

#ifndef TP1_BINARYTREE_H
#define TP1_BINARYTREE_H

#include "utils.h"

//Definição do nome do arquivo em que será criada a arvore binaria
#define BINARYTREEFILE "../binaryTree.bin"

/* Definição da estrutura que será utilizada como Nó da arvore binaria
 *
 * left = posição do item a esquerda
 * right = posição do item a direita
 * ItemType = Item que será guardado no Nó atual
 * int pos = posição do item atual
 */
typedef struct {
    int left;
    int right;
    ItemType item;
    int pos;
} BinaryNode;

//DESCRIÇÃO DAS FUNÇÕES NO ARQUIVO .C CORRESPONDENTE
void createBinaryTree();

ItemType binaryTreeSearch(FILE *binaryTree, int key);

#endif //TP1_BINARYTREE_H
