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

    while(scanf(" %c %d", &op, &num) != EOF){
        if(op == 'i'){
            inserir(t, num);
        } else if (op == 'r') {
            remover(t, num);
        }
    }

    print_em_ordem(t->root);
    destroi(t);

    return 0;
}