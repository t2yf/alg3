#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

int main(){
    char op;
    int num;

    //criar raiz
    scanf(" %c %d", &op, &num);
    struct no_t *r = cria_no(num);

    while(scanf(" %c %d", &op, &num) != EOF){
        if(op == 'i'){
            inserir(r, num);
        } else if (op == 'r') {
            //retirar
        }
    }

    print_em_ordem(r);
    

    //destruir arvore

    return 0;
}