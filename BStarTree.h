//
// Created by mathe on 4/25/2022.
//

#ifndef TP1_BSTARTREE_H
#define TP1_BSTARTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "BTree.h"

// Estrutura auxiliar para ponteiros de pagina
typedef struct PageTypeS *PointerTypeS;

/* Definição que será utilizada para definir se a pagina será interna ou
 * externa
 */
typedef enum {
    Inter,
    Extern
} IntExtType;

/* Definição da estrutura que será utilizada como Nó da arvore B estrela
 *
 * Pt = definição de externa e interna
 * int_num = Numero de registros interno
 * intern_items = Registros internos
 * inter_pointers = ponteiros para os registros filhos internos
 * ext_num = Numero externo
 * extern_items = Items externos
 * UU = paginas
 * U0 = Pagina interna
 * U1 = pagina externa
 */
typedef struct PageTypeS {
    IntExtType Pt;
    union
    {
        struct
        {
            int int_num;
            int intern_items[MM];
            PointerTypeS inter_pointers[MM + 1];
        } U0;
        struct
        {
            int ext_num;
            ItemType extern_items[MM * 2];
        } U1;
    } UU;
} PageTypeS;

//Funções comentadas no arquivo .c correspondente

int searchBStar(ItemType *item, PointerTypeS page);
void createBStarTree(FILE *file, PointerTypeS *page);
void addInStar(ItemType item, PointerTypeS *page);
void insertStarTree(ItemType item, PointerTypeS page, short *grow,
                    ItemType *item_returned, PointerTypeS *page_returned);
void insertInStarPage(PointerTypeS page, ItemType item, PointerTypeS rifht_page);

#endif //TP1_BSTARTREE_H
