#include <stdio.h>
#include <stdlib.h> 
#include "rb_tree.h"

#define BLACK 0
#define RED 1

struct no_t *cria_no(int chave){
    struct no_t *n;

    n = malloc(sizeof(struct no_t));

    n->cor = RED;
    n->dir = NULL;
    n->esq = NULL;
    n->pai = NULL;
    n->chave = chave;

    return n;
}

struct no_t *busca(struct no_t *r, int chave){
    //chave não existe
    if(!r)
        return NULL;

    if(chave == r->chave)
        return r;

    if(chave < r->chave)
        return busca(r->esq, chave);
    
    return busca(r->dir, chave);
}

void inserir_fix(struct no_t *r, int chave){
    
}

void inserir(struct no_t *r, int chave){
    struct no_t *pai, *aux;

    aux = r;

    //achar onde inserir
    while(aux != NULL){
        //salvar o pai
        pai = aux; 
        //ir para a esquerda
        if(aux->chave > chave)
            aux = aux->esq; 
        else 
            aux = aux->dir; 
    }

    //criar novo no
    aux = cria_no(chave);

    //ajustar ponteiros
    if(pai->chave > chave)
        pai->esq = aux;
    else 
        pai->dir = aux;
    
    aux->pai = pai;
}

void print_em_ordem(struct no_t *r){
    if(r == NULL) return;

    print_em_ordem(r->esq);
    printf("%d \n", r->chave);
    //    printf("%d, %d, %d \n", r->chave, nivel,r->cor);
    print_em_ordem(r->dir);
}

