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
    n->chave = chave;

    return n;
}

struct tree_t *cria_arvore(int chave){
    struct tree_t *t;

    if(!(t = malloc(sizeof(struct tree_t))))
        return NULL;

    t = cria_no(chave);

    if (t->root == NULL) {
        free(t);
        return NULL;
    }

    t->root->cor = BLACK;
    t->root->pai = NULL;

    return t;
}

void destroi_no(struct no_t *n){
    if(n != NULL){
        destroi_no(n->esq);
        destroi_no(n->dir);
        free(n);
    }
}

void destroi(struct tree_t *t){
    if(t != NULL){
        destroi_no(t->root);
        free(t);
    }
}

void rot_esq(struct tree_t *t, struct no_t *x){
    struct no_t *y;
    y = x->dir; 
    x->dir = y->esq; 

    if(y->esq != NULL)
        y->esq->pai = x;
    
    y->pai = x->pai; 

    //se x for a raiz
    if(x->pai == NULL)
        t->root = y; //y passa a ser a raiz
    else if(x == x->pai->esq)
        x->pai->esq = y; 
    
    else
        x->pai->dir = y;
    
    y->esq = x; 
    x->pai = y;
}

void rot_dir(struct tree_t *t, struct no_t *x){
    struct no_t *y;

    y = x->esq;
    x->esq = y->dir;

    if(y->dir != NULL)
        y->dir->pai = x;
    
    y->pai = x->pai;

    if(x->pai == NULL)
        t->root = y; //y passa a ser a raiz
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    
    y->dir = x;
    x->pai = y;
}


//Inserção: 
    // Inserir primeiro e depois consertar

void inserir_fixup(struct tree_t *t, struct no_t *aux){
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
                rot_esq(t, aux);
                } 
                //Caso 3**
                aux->pai->cor = BLACK;
                aux->pai->pai->cor = RED;
                //rotação entre pai e avô
                rot_dir(t, aux->pai->pai);
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
                    rot_dir(t, aux);
                }
                //Caso 3
                aux->pai->cor = BLACK;
                aux->pai->pai->cor = RED;
                rot_esq(t, aux->pai->pai);
            }
        }
    }
    //raiz sempre é preta, trata tanto colocar o primeiro nó (raiz) quanto o consertar
    t->root->cor = BLACK;
}


void inserir(struct tree_t *t, int chave){
    struct no_t *pai, *novo;
    novo = t->root;

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
    inserir_fix(t, novo);
}

/*Remover*/
    //Remover e depois consertar

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

struct no_t *tree_max(struct no_t *r){
    if(r == NULL) return NULL;

    while(r->dir != NULL){
        r = r->dir;
    }

    return r; 
}

void transplant(struct tree_t *t, struct no_t *u, struct no_t *v){
    //Se u for raiz, substitui por v
    if(u->pai == NULL)
        t->root = v;
    //Se for o filho da esquerda    
    else if(u == u->pai->esq)
        u->pai->esq = v; //v será excluido
    else 
        u->pai->dir = v;
    
    if(v != NULL) //Se v era raiz
        v->pai = u->pai;
}

void remover_fixup(struct tree_t *t, struct no_t *x){
    while(x->pai != NULL && x->cor == BLACK){
        if(x == x->pai->esq){
            struct no_t *w = x->pai->dir;
            //Caso 1
            if(w->cor == RED){
                w->cor = BLACK;
                x->pai->cor = RED;
                rot_esq(t, x->pai);
                w = x->pai->dir;
            }
            //Caso 2
            if(w->esq->cor == BLACK && w->dir->cor == BLACK){
                w->cor = RED;
                x = x->pai;
            }
            //Caso 3
            else {
                if(w->dir->cor == BLACK){
                    w->esq->cor = BLACK;
                    w->cor = RED;
                    rot_dir(t, w);
                    w = x->pai->dir;
                }
                //Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                w->dir->cor = BLACK;
                rot_esq(t, x->pai);
                x = t->root;
            }
        }
        else{
            struct no_t *w = x->pai->esq;
            //Caso 1
            if(w->cor == RED){
                x->cor = BLACK;
                x->pai->cor = RED;
                rot_dir(t, x->pai);
                w = x->pai->esq;
            }
            //Caso 2
            if(w->dir->cor == BLACK && w->esq->cor == BLACK){
                w->cor = RED;
                x = x->pai;
            }
            //Caso 3
            else{
                if(w->esq->cor == BLACK){
                    w->dir->cor = BLACK;
                    w->cor = RED;
                    rot_esq(t, w);
                    w = x->pai->esq;
                }
                //Caso 4
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                w->esq->cor = BLACK;
                rot_dir(t, x->pai);
                x = t->root;
            }
        }
    }
    x->cor = BLACK;
}

void remover(struct tree_t *t, int chave){
    struct no_t *z = busca(t->root, chave);
    struct no_t *y, *x;
    int cor;

    /*Se não achar z*/
    if(z == NULL){
        return;
    }

    /**/
    y = z;
    cor = y->cor;
    if(z->esq == NULL){
        x = z->dir;
        transplant(t, z, z->dir);
    } else if (z->dir == NULL){
        x = z->esq;
        transplant(t, z, z->esq);
    } else{
        y = tree_max(z->esq); //Antecessor
        x = y->dir;
        if(y->pai == z){
            x->pai = y;
        } else{
            transplant(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplant(t, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }

    /*Consertar*/
    if(cor == BLACK){
        remover_fixup(t, x);
    }
}

void print_em_ordem_aux(struct no_t *r, int nivel){
    if(r == NULL) return;

    print_em_ordem_aux(r->esq, nivel+1);
    printf("%d,%d,%d\n", r->chave, nivel, r->cor);
    print_em_ordem_aux(r->dir, nivel+1);
}


void print_em_ordem(struct tree_t *t){
    print_em_ordem_aux(t->root, 0);
}
