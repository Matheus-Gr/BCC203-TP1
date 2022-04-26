#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * Função responsável pela busca de um item em uma arvore B.
 * A função recebe como parâmetro a referencia de um item, e um endereço de
 * memória que representa o nó raiz da árvore.
 * A busca se baseia em :utilizar uma variável auxiliar como contadora que irá
 * servir como um localizador do indice do item dentro do array de itens da
 * página.Será então feita a comparação entre o item buscado e o item
 * referenciado pelo contador,se os itens forem iguais a busca termina,
 * retornando o item por referência e encerrando a busca com o status 1, caso os
 * itens forem diferentes , é feita uma análise se o item buscado é maior ou
 * menor que o item comparado na página corrente da árvore,caso o item buscado
 * seja maior que o item comparado a função é invocada recursivamente para o
 * apontador a direita do item atual,caso o item seja menor a função é invocada
 * recursivamente para o apontador a esquerda.Este processo é repetido até que o
 * item seja encontrado , ou o apontador a esquerda ou a direita de um item seja
 * NULL.
 *
 * item = Registro proucurado
 * Tree = Arvore
 */
int searchBTree(ItemType *item, PointerType Tree) {
    long i = 1;
    if (Tree == NULL) {
        printf ("Não existe\n_items");
        return 0;
    }
    while (i < Tree->n_items && item->key > Tree->items[i - 1].key) i++;

    if (item->key == Tree->items[i - 1].key) {
        *item = Tree->items[i - 1];
        return 1;
    }

    if (item->key < Tree->items[i - 1].key)
        return searchBTree(item, Tree->pointers[i - 1]);
    else
        return searchBTree(item, Tree->pointers[i]);
}

void Imprime(PointerType arvore) {
    int i = 0;
    if (arvore == NULL)
        return;
    while (i <= arvore->n_items) {
        Imprime(arvore->pointers[i]);
        if (i != arvore->n_items)
            printf("%d ", arvore->items[i].key);
        i++;
    }
    printf("\n");
}


void insertInPage(PointerType curPage, ItemType item,
                  PointerType right_pointer) {
    int pos_not_found;
    int k = curPage->n_items;
    pos_not_found = (k > 0);

    while (pos_not_found) {
        if (item.key >= curPage->items[k - 1].key) {
            pos_not_found = 0;
            break;
        }
        curPage->items[k] = curPage->items[k - 1];
        curPage->pointers[k + 1] = curPage->pointers[k];
        k--;
        if (k < 1) pos_not_found = 0;
    }
    curPage->items[k] = item;
    curPage->pointers[k + 1] = right_pointer;
    curPage->n_items++;
}

void recursiveInsert(ItemType item, PointerType tree, short *grow,
                     ItemType *item_returned, PointerType *right_child) {

    PointerType temp_page;

    if (tree == NULL) {
        *grow = TRUE;
        (*item_returned) = item;
        (*right_child) = NULL;
        return;
    }

    int i = 1;
    while (i < tree->n_items && item.key > tree->items[i - 1].key) i++;
    if (item.key == tree->items[i - 1].key) {
        //printf ("Ja Existe\n");
        *grow = FALSE;
        return;
    }

    if (item.key < tree->items[i - 1].key) i--;

    recursiveInsert(item, tree->pointers[i], grow,
                    item_returned, right_child);

    if (!*grow) return;
    if (tree->n_items < MM) {
        insertInPage(tree, *item_returned,
                     *right_child);
        *grow = FALSE;
        return;
    }
    //Página tem que ser dividida
    temp_page = (PointerType) malloc(sizeof(PageType));
    temp_page->n_items = 0;
    temp_page->pointers[0] = NULL;

    if (i < M + 1) {
        insertInPage(temp_page, tree->items[MM - 1],
                     tree->pointers[MM]);
        tree->n_items--;
        insertInPage(tree, *item_returned,
                     *right_child);
    } else insertInPage(temp_page, *item_returned,
                     *right_child);

    for (int j = M + 2; j <= MM; j++) {
        insertInPage(temp_page, tree->items[j - 1],
                     tree->pointers[j]);
    }

    tree->n_items = M;
    temp_page->pointers[0] = tree->pointers[M + 1];
    *item_returned = tree->items[M];
    *right_child = temp_page;

}

void insertInBTree(ItemType item, PointerType *tree) {
    short grow;
    ItemType item_returned;
    PageType *page_returned, *temp_page;

    recursiveInsert(item, *tree, &grow, &item_returned, &page_returned);

    //Se arvore crescer ela cria nova pagina raiz
    if (grow) {
        temp_page = (PageType *) malloc(sizeof(PageType));
        temp_page->n_items = 1;
        temp_page->items[0] = item_returned;
        temp_page->pointers[1] = page_returned;
        temp_page->pointers[0] = *tree;
        *tree = temp_page;
    }
}

ItemType bTreeCreateAndSearch(int key) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }
    PointerType tree = NULL;

    ItemType reg;

    while (!feof(file)) {
        fread(&reg, sizeof(ItemType), 1, file);
        insertInBTree(reg, &tree);
    }
//    Imprime(tree);
    ItemType *busca = (ItemType *) malloc(sizeof(ItemType));
    busca->key = key;
    if (searchBTree(busca, tree)) return *busca;
}