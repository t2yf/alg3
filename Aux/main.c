#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

int main(){
    struct tree_t *t = cria_arvore();
    char op;
    int num;

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

    print_em_ordem(t);
    destroi(t);

    return 0;
}