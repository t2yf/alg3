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


void rot_esq(struct no_t **r, struct no_t *x){
    struct no_t *y;
    y = x->dir; 
    x->dir = y->esq; 

    if(y->esq != NULL)
        y->esq->pai = x;
    
    y->pai = x->pai; 

    //se x for a raiz
    if(x->pai == NULL)
        *r = y; //y passa a ser a raiz
    else if(x == x->pai->esq)
        x->pai->esq = y; 
    
    else
        x->pai->dir = y;
    
    y->esq = x; 
    x->pai = y;
}

void rot_dir(struct no_t **r, struct no_t *x){
    struct no_t *y;

    y = x->esq;
    x->esq = y->dir;

    if(y->dir != NULL)
        y->dir->pai = x;
    
    y->pai = x->pai;

    if(x->pai == NULL)
        *r = y; //y passa a ser a raiz
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    
    y->dir = x;
    x->pai = y;
}

//Inserção: 
    // Inserir primeiro e depois consertar

void inserir_fix(struct no_t *r, struct no_t *aux){
    //seguir regra: nó pai de um nó vermelho é preto
    // se aux não é NULL
    while(aux->pai != NULL && aux->pai->cor == RED){ 
        //se o pai de aux é o filho da esquerda do vô 
        if(aux->pai == aux->pai->pai->esq){
            struct no_t *tio = aux->pai->pai->dir;

            if(tio->cor == RED){
                //Caso 1

                //mudar cor do vô, pai e tio
                aux->pai->pai->cor = RED;
                aux->pai->cor = RED;
                tio->cor = BLACK;
                //aux <- pai 
                aux = aux->pai->pai;
            } //se aux for o filho direito
            else{
                if (aux == aux->pai->dir){
                //Caso 2
                aux = aux->pai;
                rot_esq(r, aux);
                } 
                //Caso 3**
                aux->pai->cor = BLACK;
                aux->pai->pai->cor = RED;
                //rotação entre pai e avô
                rot_dir(r, aux->pai->pai);
            }
        //outro lado     
        } else {
            struct no_t *tio = aux->pai->pai->esq;

            if(tio->cor == RED){
                //Caso 1
                aux->pai->pai->cor = RED;
                aux->pai->cor = RED;
                tio->cor = BLACK;
                aux = aux->pai->pai;
            }
            else {
                if(aux == aux->pai->esq){
                    //Caso 2
                    aux = aux->pai;
                    rot_dir(r, aux);
                }
                //Caso 3
                aux->pai->cor = BLACK;
                aux->pai->pai->cor = RED;
                rot_esq(r, aux->pai->pai);
            }
        }
    }
    //raiz sempre é preta, trata tanto colocar o primeiro nó (raiz) quanto o consertar
    r->cor = BLACK;
}

void inserir(struct no_t *r, int chave){
    struct no_t *pai, *novo;
    novo = r;

    //achar onde inserir
    while(novo != NULL){
        //salvar o pai
        pai = novo;         
        if(novo->chave > chave)
            novo = novo->esq; 
        else 
            novo = novo->dir; 
    }

    //criar novo no
    novo = cria_no(chave);

    //ajustar ponteiros
    if(pai->chave > chave)
        pai->esq = novo;
    else 
        pai->dir = novo;
    
    novo->pai = pai;

    //consertar árvore
    inserir_fix(r, novo);
}



void print_em_ordem(struct no_t *r){
    if(r == NULL) return;

    print_em_ordem(r->esq);
    printf("%d, %d \n", r->chave, r->cor);
    //    printf("%d, %d, %d \n", r->chave, nivel,r->cor);
    print_em_ordem(r->dir);
}

