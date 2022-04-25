#include "utils.h"

#ifndef ARVOREB_H
#define ARVOREB_H

//Tipagem
#define M 32
#define MM (M*2)

typedef struct PageType* PointerType;

typedef struct PageType{
    short n_items;
    ItemType items[MM];
    PointerType pagePointers[MM + 1];
} PageType;

//--------Funções --------
//função de inicialização
void Inicializa (PointerType Arvore);
//função de pesquisa
int searchBTree (ItemType *x, PointerType Tree);
//função de caminhamento e de impressão dos dados em uma arvore
void Imprime(PointerType arvore);
//funções de inserção
void insertInPage (PointerType curPage, ItemType item, PointerType rightPointer);
void recursiveInsert (ItemType item, PointerType tree, short *grow, ItemType *item_returned, PointerType *right_child);
void insertInBTree (ItemType item, PointerType *tree);
//função específica do TP
ItemType bTreeCreateAndSearch (int key);

#endif