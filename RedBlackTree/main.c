#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

int main(){
    char op;
    int num;

    /*Criar raiz*/
    scanf(" %c %d", &op, &num);
    struct tree_t *t = cria_arvore(num);

    /*Caso não crie a raiz*/
    if(t == NULL){
        return 1;
    }

    fprintf(stderr, "Arvore criada, com raiz %d\n", t->root->chave);
    

    while(scanf(" %c %d", &op, &num) != EOF){
        if(op == 'i'){
            fprintf(stderr, "Inserir: %d\n", num);
            inserir(t, num);
        } else if (op == 'r') {
            fprintf(stderr, "Remover: %d\n", num);
            remover(t, num);
        }
    }

    print_em_ordem(t);
    destroi(t);

    return 0;
}