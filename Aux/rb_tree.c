#include <stdio.h>
#include <stdlib.h>
#include "rb_tree.h"

#define BLACK 0
#define RED 1

struct tree_t *cria_arvore(){
    struct tree_t *t;

    if(!(t = malloc(sizeof(struct tree_t))))
        return NULL;

    if(!(t->nil = malloc(sizeof(struct no_t))))
        return NULL;
    
    t->nil->cor = BLACK;
    t->nil->esq = NULL;
    t->nil->dir = NULL;
    t->nil->pai = NULL;
    t->root = t->nil;

    return t;
}

void rot_esq(struct tree_t *t, struct no_t *x){
    struct no_t *y = x->dir;
    x->dir = y->esq;
    if(y->esq != t->nil){
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == t->nil){
        t->root = y;
    } else if(x == x->pai->esq){
        x->pai->esq = y;
    } else {
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
}

void rot_dir(struct tree_t *t, struct no_t *x){
    struct no_t *y = x->esq;
    x->esq = y->dir;
    if(y->dir != t->nil){
        y->dir->pai = x;
    }
    y->pai = x->pai;
    if(x->pai == t->nil){
        t->root = y;
    } else if(x == x->pai->dir){
        x->pai->dir = y;
    } else {
        x->pai->esq = y;
    }
    y->dir = x;
    x->pai = y;
}

void inserir_fixup(struct tree_t *t, struct no_t *z){
    while(z->pai->cor == RED){
        if(z->pai == z->pai->pai->esq){
            struct no_t *y = z->pai->pai->dir;
            if(y->cor == RED){
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;
            } else{
                if(z == z->pai->dir){
                    z = z->pai;
                    rot_esq(t, z);
                }
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                rot_dir(t, z->pai->pai);
            }
        } else {
            struct no_t *y = z->pai->pai->esq;
            if(y->cor == RED){
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;
            } else{
                if(z == z->pai->esq){
                    z = z->pai;
                    rot_dir(t, z);
                }
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                rot_esq(t, z->pai->pai);
            }
        }
    }
    t->root->cor = BLACK;
}

struct no_t *cria_no(struct tree_t *t, int chave){
    struct no_t *n;

    if(!(n = malloc(sizeof(struct no_t))))
        return NULL;

    n->cor = RED;
    n->dir = t->nil;
    n->esq = t->nil;
    n->chave = chave;
    n->pai = t->nil;

    return n;
}

void inserir(struct tree_t *t, int chave){
    struct no_t *z = cria_no(t, chave);

    if(z == NULL){
        return;
    }

    struct no_t *y = t->nil;
    struct no_t *x = t->root;

    while(x != t->nil){
        y = x;
        if(z->chave < x->chave){
            x = x->esq;
        } else{
            x = x->dir;
        }
    }

    z->pai = y;
    //Inserir raiz
    if(y == t->nil){
        t->root = z;
    } else if(z->chave < y->chave){
        y->esq = z;
    } else {
        y->dir = z;
    }
    inserir_fixup(t, z);
}

struct no_t *busca(struct no_t *r, int chave){
    //Chave não existe
    if(!r)
        return NULL;
    if(chave == r->chave)
        return r;
    if(chave < r->chave)
        return busca(r->esq, chave);
    return busca(r->dir, chave);
}

struct no_t *tree_max(struct tree_t *t, struct no_t *r){
    while(r->dir != t->nil){
        r = r->dir;
    }
    return r;
}

void transplant(struct tree_t *t, struct no_t *u, struct no_t *v){
    //Se u for raiz, substitui por v
    if(u->pai == NULL){
        t->root = v;
    }
        
    else if(u == u->pai->esq){
        u->pai->esq = v; 
    }
    else {
        u->pai->dir = v;
    }
    
    if(v != NULL) //Se v era raiz
        v->pai = u->pai;
}

void remove_fixup(struct tree_t *t, struct no_t *x){
    while(x != t->root && x->cor == BLACK){
        fprintf(stderr, "fixup\n");
        fprintf(stderr, "x %d\n", x->chave);
        fprintf(stderr, "x->pai->esq %d\n", x->pai->esq->chave);
        if(x == x->pai->esq){
            

            struct no_t *w = x->pai->dir;
            if(w->cor == RED){
                fprintf(stderr, "fixup a\n");
                w->cor = BLACK;
                x->pai->cor = RED;
                rot_esq(t, x->pai);
                w = x->pai->dir;
            }
            if(w->esq->cor == BLACK && w->dir->cor == BLACK){
                fprintf(stderr, "fixup b\n");
                w->cor = RED;
                x = x->pai;
            } else {
                if(w->dir->cor == BLACK){
                    fprintf(stderr, "fixup c\n");
                    w->esq->cor = BLACK;
                    w->cor = RED;
                    rot_dir(t, w);
                    w = x->pai->dir;
                }
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                w->dir->cor = BLACK;
                rot_esq(t, x->pai);
                x = t->root;
            }
        } else {
            struct no_t *w = x->pai->esq;
            if(w->cor == RED){
                fprintf(stderr, "fixup d\n");
                w->cor = BLACK;
                x->pai->cor = RED;
                rot_dir(t, x->pai);
                w = x->pai->esq;
            }
            if(w->dir->cor == BLACK && w->esq->cor == BLACK){
                fprintf(stderr, "fixup e\n");
                w->cor = RED;
                x = x->pai;
            } else {
                if(w->esq->cor == BLACK){
                    fprintf(stderr, "fixup f\n");
                    w->dir->cor = BLACK;
                    w->cor = RED;
                    rot_esq(t, w);
                    w = x->pai->esq;
                }
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
    //Não encontrou a chave
    if(z == NULL || z == t->nil){
        return;
    }

    struct no_t *y = z;
    struct no_t *x;
    char y_cor_orig = y->cor;

    if(z->esq == t->nil){
        x = z->dir;
        transplant(t, z, z->dir);
    } else if(z->dir == t->nil){
        x = z->esq;
        transplant(t, z, z->esq);
    } else {
        //Antecessor
        y = tree_max(t, z->esq);
        y_cor_orig = y->cor;
        x = y->esq;
        if(y->pai == z){
            if(x != t->nil)
                x->pai = y;
        } else {
            transplant(t, y, y->esq);
            y->esq = z->esq;
            y->esq->pai = y;
        }
        transplant(t, z, y);
        y->dir = z->dir;
        y->dir->pai = y;
        y->cor = z->cor;
    }
    if(y_cor_orig == BLACK){
        
        remove_fixup(t, x);
    }
    free(z);
}

void print_em_ordem_aux(struct tree_t *t, struct no_t *r, int nivel){
    if(r == t->nil) return;

    print_em_ordem_aux(t, r->esq, nivel+1);
    printf("%d,%d,%d\n", r->chave, nivel, r->cor);
    print_em_ordem_aux(t, r->dir, nivel+1);
}


void print_em_ordem(struct tree_t *t){
    print_em_ordem_aux(t, t->root, 0);
}

void destroi_aux(struct tree_t *t, struct no_t *x){
    if(x != t->nil){
        destroi_aux(t, x->esq);
        destroi_aux(t, x->dir);
        free(x);
    }
}

void destroi(struct tree_t *t){
    destroi_aux(t, t->root);
    free(t->nil);
    free(t);
}