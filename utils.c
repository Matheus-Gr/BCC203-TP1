//
// Created by mathe on 3/22/2022.
//

#include "utils.h"

/* Função responsavel por validar os argumentos passados ao executar o programa
 * afim de evitar errors de tipagem e afins
 *
 * argc = Quantidade de argumentos passados
 * method = Argumento que define qual metodo sera utilizado
 * total_items = Argumento que define a quantidade de arquivos
 * order = Argumento que define a ordem dos registros
 * key = Argumento que define a chave a ser procurada pelo programa
 * show_result = Argumento OPICIONAL que define se a tabela será de todos os
 * arquivos será mostrada no terminal
 */
void validateArguments(int argc, int method, int total_items, int order,
                       int key, char *show_result) {
    if (argc < 2) {
        printf("Must pass at least 4 arguments,"
               " <method> <total_items> <order> <key>");
        exit(1);
    } else if (method < 1 || method > 4) {
        printf("method must be between 1 and 4");
        exit(1);
    } else if (total_items == 0) {
        printf("total_items must be different from 0");
        exit(1);
    } else if (order < 1 || order > 3) {
        printf("order must be between 1 and 3");
        exit(1);
    } else if (key < 0) {
        printf("Invalid key, must be positive integer");
        exit(1);
    } else if (show_result != NULL && strcmp("-P", show_result) != 0) {
        printf("Invalid optional parameter %s", show_result);
        exit(1);
    }
}

/* Função responsavel por gerar aleatoriamente uma String totalmente aleatoria
 * de 5000 caracteres que será utilizada para prencher o campo 'data2' dos
 * registros
 *
 * return = String gerada
 */
char *randString() {
    char nullStr[] = "";
    char *text = (char *) malloc(5001 * sizeof(char));
    strcpy(text, nullStr);

    char current_char;
    char str_base[] = "0123456789"
                      "abcdefghijklmnopqrstuvwxyz"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 5000; ++i) {
        current_char = str_base[rand() % (sizeof(str_base) - 1)];
        strncat(text, &current_char, 1);
    }
    return text;
}

/* Função responsavel por gerar o arquivo que serão realizadas as consultas,
 * contendo todos os registros na ordem desejada
 *
 * total_items = Total de registros que serão criados
 * order = ordem que serão gerados os registros, sendo:
 *      1 para Crescente
 *      2 para Decrescente
 *      3 para Aletório
 */
void generateFile(int total_items, int order) {
    FILE *file = fopen(FILENAME,"wb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

    ItemType item;
    srand(time(NULL));

    int random_array[total_items];

    int duplicated = 0;

    switch (order) {
        case 1:
            for (int i = 0; i < total_items; ++i) {
                item.key = i + 1;
                item.data1 = rand() % LONG_MAX;
                char *text = randString();
                strcpy(item.data2, text);
                fwrite(&item, sizeof(ItemType), 1, file);
            }
            break;

        case 2:
            for (int i = total_items; i > 0; --i) {
                item.key = i;
                item.data1 = rand() % LONG_MAX;
                char *text = randString();
                strcpy(item.data2, text);
                fwrite(&item, sizeof(ItemType), 1, file);
            }
            break;

        case 3:
            for (int i = 0; i < total_items; ++i) random_array[i] = -1;

            for (int i = 0; i < total_items; ++i) {
                do {
                    item.key = rand() % total_items + 1;
                    random_array[i] = item.key;
                    int occurancy = 0;
                    for (int j = 0; j < total_items; ++j) {
                        if (random_array[j] == item.key) occurancy++;
                    }
                    duplicated = occurancy > 1 ? 1 : 0;
                } while (duplicated);
//                printf("key = %d     total filed: %d\n",item.key,i+1);
                item.data1 = rand() % LONG_MAX;
                char *text = randString();
                strcpy(item.data2, text);
                fwrite(&item, sizeof(ItemType), 1, file);
            }
            break;

        default:
            break;
    }

    fclose(file);
}

/* Função responsavel por imprimir na tela o arquivo desejado
 *
 * filename = String contendo nome do arquivo desejado
 */
void readFile(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }
    ItemType item;

    while (fread(&item, sizeof(ItemType), 1, file))
        printf("key: %-15d data1: %-15ld data2: %.5s\n",
               item.key, item.data1, item.data2);
    fclose(file);
}
