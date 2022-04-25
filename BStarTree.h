//
// Created by mathe on 4/25/2022.
//

#ifndef TP1_BSTARTREE_H
#define TP1_BSTARTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "BTree.h"

//Estruturas
typedef struct PageTypeS *PointerTypeS;

typedef enum {
    Inter,
    Extern
} IntExtType;

typedef struct PageTypeS {
    IntExtType Pt;
    union
    {
        struct
        { //Pagina interna
            int int_num;
            int intern_items[MM];
            PointerTypeS inter_pointers[MM + 1];
        } U0;
        struct
        { //Pagina externa (folha)
            int ext_num;
            ItemType extern_items[MM * 2];
        } U1;
    } UU;
} PageTypeS;

//Protótipos de funções
int searchBStar(ItemType *item, PointerTypeS page);
void createBStarTree(FILE *file, PointerTypeS *page);
void addInStar(ItemType item, PointerTypeS *page);
void insertStarTree(ItemType item, PointerTypeS page, short *grow,
                    ItemType *item_returned, PointerTypeS *page_returned);
void insertInStarPage(PointerTypeS page, ItemType item, PointerTypeS rifht_page);

#endif //TP1_BSTARTREE_H
