//
// Created by mathe on 4/24/2022.
//

#ifndef TP1_INDEXED_H
#define TP1_INDEXED_H

#include "utils.h"
//Responsavel por definir a quantidade de registros por pagina
#define ITEMSPERPAGE 20

//DESCRIÇÃO DAS FUNÇÕES NO ARQUIVO .C CORRESPONDENTE

void createIndexTable(int *index_table, int n_pages);

ItemType indexedSearch(const int *index_table, int key, int n_pages,
                       int total_items);

#endif //TP1_INDEXED_H
