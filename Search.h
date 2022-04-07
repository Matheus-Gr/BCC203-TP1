//
// Created by mathe on 3/22/2022.
//

#ifndef TP1_SEARCH_H
#define TP1_SEARCH_H

#include <math.h>
#include "utils.h"

void createPages(int *index_table, int n_pages);

ItemType indexedSequentialAccess(const int *index_table, int key, int n_pages);

#endif //TP1_SEARCH_H
