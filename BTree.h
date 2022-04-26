#include "utils.h"

#ifndef ARVOREB_H
#define ARVOREB_H

//Definição da ORDEM M da arvore B
#define M 32
#define MM (M*2)

// Estrutura auxiliar para ponteiros de pagina
typedef struct PageType* PointerType;

/* Definição da estrutura que será utilizada como pagina da arvore
 *
 * n_items = contem a quantidade de registros da pagina atual
 * items = contem os registros da pagina atual
 * pointers = contem os ponteiros para as paginas filhas
 */
typedef struct PageType{
    short n_items;
    ItemType items[MM];
    PointerType pointers[MM + 1];
} PageType;

//Funções comentadas no arquivo .c correspondente

int searchBTree (ItemType *x, PointerType Tree);

void Imprime(PointerType arvore);

void insertInPage (PointerType curPage, ItemType item, PointerType right_pointer);
void recursiveInsert (ItemType item, PointerType tree, short *grow, ItemType *item_returned, PointerType *right_child);
void insertInBTree (ItemType item, PointerType *tree);

ItemType bTreeCreateAndSearch (int key);

#endif