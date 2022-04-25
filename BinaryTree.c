//
// Created by mathe on 4/24/2022.
//

#include "BinaryTree.h"

/* Responsável por converter o arquivo de registro para um arquivo de arvore
 * binaria em memoria principal. Para isso é aberto aberto 2 arquivos,
 * 'binaryTree' onde será criada a arvore em modo de ESCRITA E LEITURA,
 * e 'file' em modo de LEITURA contendo previamente os registros. O arquivo
 * 'file' será lido item por item até o fim do mesmo, dentro da repetição
 * reponsável por essa tarefa, será utilizado um Nó 'child' para "converter"
 * o registro em um Nó da arvore. Após o primeiro item, que será a raiz,
 * o algoritimo irá "rebobinar" o arquivo da arvore binária, e lerá da raiz para
 * baixo os nós ja existentes e comparando, se a chave for menor que a do Nó
 * comparado, então é encaminhado para esquerda do arquivo até chegar a um Nó
 * vazio e caso maior ele emcaminha para a direita ate chegar tambem a um Nó
 * igualmente vazio, ao chegar no Nó vazio a variavel 'notEmpty' é atualizada
 * e o registro é colocado naquela posição.
 */
void createBinaryTree() {
    FILE *binaryTree = fopen(BINARYTREEFILE, "wb+");
    if (binaryTree == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }

    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Error ao abrir arquivo!\n");
        exit(1);
    }
    ItemType item;
    BinaryNode child;
    BinaryNode aux;

    int cont = 0;
    int childPos;
    int notEmpty;
    while (fread(&item, sizeof(ItemType), 1, file)) {
        notEmpty = 1;
        child.right = -1;
        child.left = -1;
        child.item = item;
        child.pos = cont;

        fwrite(&child, sizeof(BinaryNode), 1, binaryTree);
        cont++;

        if (cont != 1) {
            rewind(binaryTree);
            childPos = 0;
            while (fread(&aux, sizeof(BinaryNode),
                         1, binaryTree) && notEmpty) {
                if (item.key < aux.item.key)
                    if (aux.left == -1) {
                        aux.left = cont - 1;
                        fseek(binaryTree,
                              (int) (childPos * sizeof(BinaryNode)),
                              SEEK_SET);
                        fwrite(&aux, sizeof(BinaryNode),
                               1, binaryTree);
                        notEmpty = 0;
                    } else {
                        fseek(binaryTree,
                              (int) (aux.left * sizeof(BinaryNode)),
                              SEEK_SET);
                        childPos = aux.left;
                    }
                else {
                    if (aux.right == -1) {
                        aux.right = cont - 1;
                        fseek(binaryTree,
                              (int) (childPos * sizeof(BinaryNode)),
                              SEEK_SET);
                        fwrite(&aux, sizeof(BinaryNode),
                               1, binaryTree);
                        notEmpty = 0;
                    } else {
                        fseek(binaryTree,
                              (int) (aux.right * sizeof(BinaryNode)),
                              SEEK_SET);
                        childPos = aux.right;
                    }
                }
            }
        }
        fseek(binaryTree, 0, SEEK_END);
    }

    fclose(binaryTree);
    fclose(file);
}

/* Função responsável pela busca na arvore binaria. A busca é feita de modo
 * recursivo, sempre lendo o arquivo e comparando o registro lido que é guardado
 * em uma variavle auxiliar 'nodeAux', com a chave procurada. Caso a chave
 * proucurada for menor que a do registro lido ele encaminha para esquerda
 * utilizando a variavel 'left' para saber a posição do registro a esquerda até
 * encontrar o item necessario ou não haver mais items a esquerda, 'left = -1',
 * do mesmo modo para caso maior porem para o lado direito usando o paramentro
 * 'right'. Sendo assim retornando o registro assim que encontra o registro com
 * chave igual a procurada, ou retornando um item vazio caso não encontre
 *
 * binaryTree = arquivo que contem a arvore binaria construido
 * key = chave proucurada
 *
 * return = Item procurado ou item vazio
 */
ItemType binaryTreeSearch(FILE *binaryTree, int key) {
    BinaryNode nodeAux;
    fread(&nodeAux, sizeof(BinaryNode), 1, binaryTree);
    if (nodeAux.item.key == key) {
        return nodeAux.item;
    } else if (key > nodeAux.item.key && nodeAux.right != -1) {
        fseek(binaryTree,
              (int) (nodeAux.right * sizeof(BinaryNode)),
              SEEK_SET);
        return (binaryTreeSearch(binaryTree, key));
    } else if (key < nodeAux.item.key && nodeAux.left != -1) {
        fseek(binaryTree,
              (int) (nodeAux.left * sizeof(BinaryNode)),
              SEEK_SET);
        return (binaryTreeSearch(binaryTree, key));
    }

    return nodeAux.item;
}