//
// Created by mathe on 4/25/2022.
//

#include "BStarTree.h"

//O metodo de pesquisa ira retornar 0 caso nao encontre o item, e 1 caso encontre
int searchBStar(ItemType *item, PointerTypeS page) {
    long i;

    if (page == NULL) {
        printf("Arvore vazia\n");
        return 0;
    }

    //Pesquisa sequencial na pagina interna
    if (page->Pt == Inter) {
        i = 1;

        while ((i < page->UU.U0.int_num) &&
               (item->key > page->UU.U0.intern_items[i - 1])) i++;

        //Pesquisa recursiva até encontrar uma página folha
        if (item->key < page->UU.U0.intern_items[i - 1])
            return searchBStar(item, page->UU.U0.inter_pointers[i - 1]);
        else
            return searchBStar(item, page->UU.U0.inter_pointers[i]);
    }
    //Pesquisa sequencial na pagina folha
    i = 1;
    while ((i < page->UU.U1.ext_num) &&
            (item->key > page->UU.U1.extern_items[i - 1].key)) i++;

    if (item->key == page->UU.U1.extern_items[i - 1].key) {
        *item = page->UU.U1.extern_items[i - 1];
        return 1;
    } else{
        return 0;
    }
}

//O metodo createBStarTree eh responsavel por criar a arvore B* em memoria principal, tendo Ap como o ponteiro
//para a raiz dessa arvore B*
void createBStarTree(FILE *file, PointerTypeS *page) {
    ItemType item;

    while (fread(&item, sizeof(ItemType), 1, file)) {
        addInStar(item, page);
    }
}

void addInStar(ItemType item, PointerTypeS *page) {
    short grow;
    ItemType item_returned;
    PageTypeS *page_returned;
    PageTypeS *aux_page;

    //Insercao do primeiro item em uma arvore B* vazia
    if (*page == NULL) {
        aux_page = (PageTypeS *) malloc(sizeof(PageTypeS));
        aux_page->Pt = Extern;
        aux_page->UU.U1.ext_num = 1;
        aux_page->UU.U1.extern_items[0] = item;
        *page = aux_page;
        return;
    } else { //Insercao dos demais itens
        insertStarTree(item, *page, &grow,
                       &item_returned, &page_returned);
        //Arvore grow na altura pela raiz
        if (grow) {
            aux_page = (PageTypeS *) malloc(sizeof(PageTypeS));
            aux_page->Pt = Inter;
            aux_page->UU.U0.int_num = 1;
            aux_page->UU.U0.intern_items[0] = item_returned.key;
            aux_page->UU.U0.inter_pointers[1] = page_returned;
            aux_page->UU.U0.inter_pointers[0] = *page;
            *page = aux_page;
        }
    }
}

void insertStarTree(ItemType item, PointerTypeS page, short *grow,
                    ItemType *item_returned, PointerTypeS *page_returned) {
    long i = 1;
    long j;
    PointerTypeS aux_pointer;

    //Caso a pagina seja externa (folha)
    if (page->Pt == Extern) {
        while ((i < page->UU.U1.ext_num && item.key) >
               (page->UU.U1.extern_items[i - 1].key)) i++;

        if (item.key == page->UU.U1.extern_items[i - 1].key) {
            printf("Registro ja esta presente\n");
            *grow = FALSE;
            return;
        }

        if (item.key < page->UU.U1.extern_items[i - 1].key) i--;

        //Página tem espaço
        if (page->UU.U1.ext_num < MM) {
            *item_returned = item;
            insertInStarPage(page, *item_returned, *page_returned);
            *grow = FALSE;
            return;
        }
        //Página tem que ser dividida
        aux_pointer = (PageTypeS *) malloc(sizeof(PageTypeS));
        aux_pointer->Pt = Extern;
        aux_pointer->UU.U1.ext_num = 0;

        *item_returned = item;  //retorno recebe o item
        *page_returned = NULL; //apontador recebe NULL

        //Nova página com novo registro
        if (i < M + 1) {
            insertInStarPage(aux_pointer,
                             page->UU.U1.extern_items[MM - 1],
                             *page_returned);
            page->UU.U1.ext_num--;
            insertInStarPage(page, *item_returned,
                             *page_returned);
        } else {
            insertInStarPage(aux_pointer, *item_returned,
                             *page_returned);
        }
        //Empurrando
        for (j = 1; j <= M; j++) {
            insertInStarPage(aux_pointer,
                             page->UU.U1.extern_items[MM - j],
                             *page_returned);
        }

        page->UU.U1.ext_num = M;
        *item_returned = page->UU.U1.extern_items[M];
        *page_returned = aux_pointer;
        *grow = TRUE;
        return;
    } else { //Caso a pagina seja externa (folha)
        //Mesmo que Árvore B
        while ((i < page->UU.U0.int_num && item.key) >
               (page->UU.U0.intern_items[i - 1]))
            i++;

        if (item.key == page->UU.U0.intern_items[i - 1]) {
            printf("Registro ja esta presente\n");
            *grow = FALSE;
            return;
        }

        if (item.key < page->UU.U0.intern_items[i - 1]) i--;

        insertStarTree(item, page->UU.U0.inter_pointers[i],
                       grow, item_returned, page_returned);
        if (!*grow) return;
        //Página tem espaço
        if (page->UU.U0.int_num < MM) {
            insertInStarPage(page, *item_returned,
                             *page_returned);
            *grow = FALSE;
            return;
        }
        //Página tem que ser dividida: cria-se uma nova página
        aux_pointer = (PageTypeS *) malloc(sizeof(PageTypeS));
        aux_pointer->Pt = Inter;
        aux_pointer->UU.U0.int_num = 0;
        aux_pointer->UU.U0.inter_pointers[0] = NULL;

        ItemType aux_item;

        if (i < M + 1) {
            //Lending ou empréstimo
            aux_item.key = page->UU.U0.intern_items[MM - 1];
            insertInStarPage(aux_pointer, aux_item,
                             page->UU.U0.inter_pointers[MM]);
            page->UU.U0.int_num--;
            insertInStarPage(page, *item_returned,
                             *page_returned);
        } else {
            insertInStarPage(aux_pointer, *item_returned,
                             *page_returned);
        }

        for (j = M + 2; j <= MM; j++) {
            aux_item.key = page->UU.U0.intern_items[j - 1];
            insertInStarPage(aux_pointer, aux_item,
                             page->UU.U0.inter_pointers[j]);
        }

        page->UU.U0.int_num = M;
        aux_pointer->UU.U0.inter_pointers[0] = page->UU.U0.inter_pointers[M + 1];
        item_returned->key = page->UU.U0.intern_items[M];
        *page_returned = aux_pointer;

        return;
    }
}

void insertInStarPage(PointerTypeS page, ItemType item,
                      PointerTypeS rifht_page) {
    short pos_not_found = FALSE;
    int k;

    //Caso a pagina seja externa (folha)
    //Comportamento igual o da árvore B
    if (page->Pt == Extern) {
        k = page->UU.U1.ext_num;
        if (k > 0) pos_not_found = TRUE;
        //Busca a posição da key na página
        while (pos_not_found) {
            //Verifica a posição do novo registro na página
            if (item.key >= page->UU.U1.extern_items[k - 1].key) {
                pos_not_found = FALSE;
                break;
            }
            //Empurra os registros pra frente
            page->UU.U1.extern_items[k] = page->UU.U1.extern_items[k - 1];
            k--;
            if (k < 1) pos_not_found = FALSE;
        }
        page->UU.U1.extern_items[k] = item;
        page->UU.U1.ext_num++;
    } else { //Caso a pagina seja interna
        k = page->UU.U0.int_num;
        if (k > 0) pos_not_found = TRUE;
        //Busca a posição da key na página
        while (pos_not_found) {
            //Verifica a posição do novo registro na página
            if (item.key >= page->UU.U0.intern_items[k - 1]) {
                pos_not_found = FALSE;
                break;
            }
            //Empurra os registros pra frente
            page->UU.U0.intern_items[k] = page->UU.U0.intern_items[k - 1];
            page->UU.U0.inter_pointers[k + 1] = page->UU.U0.inter_pointers[k];
            k--;
            if (k < 1) pos_not_found = FALSE;
        }

        page->UU.U0.intern_items[k] = item.key;
        page->UU.U0.inter_pointers[k + 1] = rifht_page;
        page->UU.U0.int_num++;
    }
}