//
// Created by mathe on 4/24/2022.
//

#include "Indexed.h"

/* Responsavel por criar a tabela de indexes, que será utilizada como uma
 * paginação. A tabela 'index_table' de tamanho 'n_pages' será prenchida com
 * o valor da chave do primeiro item da "pagina" correspondente, "pagina" essa
 * definida pelo tamanho 'ITEMSPERPAGE', que dara "saltos" no arquivo com este
 * tamanho definido.
 *
 * index_table = tabela que será passada por parâmetro contendo os indexes
 * n_pages = numero de "paginas" que define o tamanho da tabela de indexes
 */
void createIndexTable(int *index_table, int n_pages) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }
    ItemType item;

    for (int i = 0; i < n_pages; ++i) {
        fread(&item, sizeof(item), 1, file);
        index_table[i] = item.key;
        for (int j = 0; j < ITEMSPERPAGE - 1; ++j)
            fread(&item, sizeof(item), 1, file);
    }

    fclose(file);
}

/* Este é o algoritimo resposável pelo processo de busca no arquivo indexado.
 * Tendo em vista que o arquivo contendo os registro precisa estar ordenado,
 * a busca utiliza o vetor 'index_table' que conta em cada posição a chave que
 * representa o index da pagina de mesma posição, o algoritimo compara a chave
 * solicita com as chaves dos index. Ao achar uma determinada chave MAIOR que
 * a procurada, indica que o item procurado esta na pagina anterior. Assim
 * então o algoritimo busca somente aquela chave necessária, lendo então
 * registro por registro até encontrar o solicitado
 *
 * index_table = Table que contem os indexes
 * key = chave do registro proucurado
 * n_pages = Número total de páginas
 * total_items = Número total de registros no arquivo
 *
 * return = Item proucurado
 */
ItemType indexedSearch(const int *index_table,
                       int key, int n_pages,int total_items) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

    for (int i = 0; i < n_pages; ++i) {
//        printf("\n%d < %d || ( %d >= %d && %d <= %d)\n",
//               key, index_table[i], key, index_table[n_pages - 1],
//               key, total_items);
        if (key < index_table[i] ||
            (key >= index_table[n_pages - 1] && key <= total_items)) {
            int aux = i - 1;
            if (key >= index_table[n_pages - 1]) aux = i + 1;
            long offset = (long) ((aux) * ITEMSPERPAGE * sizeof(ItemType));
            fseek(file, offset, SEEK_SET);
            ItemType item_page[ITEMSPERPAGE];
            fread(&item_page, sizeof(ItemType),
                  ITEMSPERPAGE, file);
            for (int j = 0; j < ITEMSPERPAGE; j++) {
//                printf("%d == %d \n_items",item_page[j].key, key);
                if (item_page[j].key == key) return item_page[j];
            }
        }
    }
    printf("Key %d not found!!",key);
    fclose(file);
    exit(1);
}