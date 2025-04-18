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

    t->root = cria_no(chave);

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
    fprintf(stderr, "Entrou fixup\n");
    fprintf(stderr, "Pai do novo: %d, %d\n", aux->pai->chave, aux->pai->cor);
    while(aux->pai != NULL && aux->pai->cor == RED){ 
        //se o pai de aux é o filho da esquerda do vô 
        if(aux->pai == aux->pai->pai->esq){
            struct no_t *tio = aux->pai->pai->dir;
            fprintf(stderr, "If a\n");
            if(tio != NULL && tio->cor == RED){
                //Caso 1

                //mudar cor do vô, pai e tio
                aux->pai->pai->cor = RED;
                aux->pai->cor = BLACK;
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
            fprintf(stderr, "Else b\n");
            fprintf(stderr, "Caso 1 ->b\n");
            if(tio != NULL && tio->cor == RED){
                //Caso 1
                fprintf(stderr, "Caso 1 ->b\n");
                aux->pai->pai->cor = RED;
                aux->pai->cor = RED;
                tio->cor = BLACK;
                aux = aux->pai->pai;
            }
            else {
                fprintf(stderr, "Caso 2 ->b\n");
                if(aux == aux->pai->esq){
                    //Caso 2
                    fprintf(stderr, "Caso 2 ->b\n");
                    aux = aux->pai;
                    rot_dir(t, aux);
                }
                //Caso 3
                fprintf(stderr, "Caso 3 ->b\n");
                aux->pai->cor = BLACK;
                aux->pai->pai->cor = RED;
                fprintf(stderr, "Executar Caso 3: %d\n", aux->chave);

                rot_esq(t, aux->pai->pai);
            }
        }
    }
    //raiz sempre é preta, trata tanto colocar o primeiro nó (raiz) quanto o consertar
    t->root->cor = BLACK;

    fprintf(stderr, "Nodo: %d, %d\n", aux->chave, aux->cor);
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
    fprintf(stderr, "Nodo novo à criar %d\n", chave);
    novo = cria_no(chave);
    fprintf(stderr, "Nodo novo criado %d\n", novo->chave);

    //ajustar ponteiros
    if(pai->chave > chave)
        pai->esq = novo;
    else 
        pai->dir = novo;
    
    novo->pai = pai;

    

    //consertar árvore
    inserir_fixup(t, novo);

    fprintf(stderr, "Nodo novo colocado no lugar certo %d\n", novo->chave);
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
    fprintf(stderr, "Entrou transplante\n");
    //Se u for raiz, substitui por v
    if(u->pai == NULL){
        t->root = v;
        fprintf(stderr, "Caso 1\n");
    }
        
    //Se for o filho da esquerda    
    else if(u == u->pai->esq){
        fprintf(stderr, "Caso 2\n");
        u->pai->esq = v; //v será excluido
    }
    else {
        fprintf(stderr, "Caso 3\n");
        u->pai->dir = v;
    }
        
    
    if(v != NULL) //Se v era raiz
        v->pai = u->pai;
}

void remover_fixup(struct tree_t *t, struct no_t *x){
    fprintf(stderr, "Entrou no remove fixup\n");
   
    while(x != t->root && x->cor == BLACK){
        if(x == x->pai->esq){
            struct no_t *w = x->pai->dir;
            fprintf(stderr, "Caso 1a\n");
            //Caso 1
            if(w->cor == RED){
                w->cor = BLACK;
                x->pai->cor = RED;
                rot_esq(t, x->pai);
                w = x->pai->dir;
            }
            //Caso 2
            if(w->esq->cor == BLACK && w->dir->cor == BLACK){
                fprintf(stderr, "Caso 2a\n");
                w->cor = RED;
                x = x->pai;
            }
            //Caso 3
            else {
                if(w->dir->cor == BLACK){
                    fprintf(stderr, "Caso 3a\n");
                    w->esq->cor = BLACK;
                    w->cor = RED;
                    rot_dir(t, w);
                    w = x->pai->dir;
                }
                //Caso 
                fprintf(stderr, "Caso 4a\n");
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
                fprintf(stderr, "Caso 1b\n");
                x->cor = BLACK;
                x->pai->cor = RED;
                rot_dir(t, x->pai);
                w = x->pai->esq;
            }
            //Caso 2
            if(w->dir->cor == BLACK && w->esq->cor == BLACK){
                fprintf(stderr, "Caso 2b\n");
                w->cor = RED;
                x = x->pai;
            }
            //Caso 3
            else{
                if(w->esq->cor == BLACK){
                    fprintf(stderr, "Caso 3b\n");
                    w->dir->cor = BLACK;
                    w->cor = RED;
                    rot_esq(t, w);
                    w = x->pai->esq;
                }
                //Caso 4
                fprintf(stderr, "Caso 4b\n");
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
    fprintf(stderr, "Entrou remover\n");
    struct no_t *z = busca(t->root, chave);

    if(z == NULL)
        return;

    struct no_t *y = z;
    struct no_t *x;
    int y_cor_orig = y->cor;

    if(z->esq == NULL){
        fprintf(stderr, "a\n");
        x = z->dir;
        transplant(t, z, z->dir);
        // if(z->pai == NULL)
        //     t->root = x;
        // else if(z == z->pai->esq)
        //     z->pai->esq = x;
        // else
        //     z->pai->dir = x;
        
        // if (x != NULL)
        //     x->pai = z->pai;
    } else if(z->dir == NULL){
        fprintf(stderr, "b\n");
        x = z->esq;
        transplant(t, z, z->esq);
        // if(z->pai == NULL)
        //     t->root = x;
        // else if(z == z->pai->esq)
        //     z->pai->esq = x;
        // else
        //     z->pai->dir = x;

        // if (x != NULL)
        //     x->pai = z->pai;
    } else {
        y = tree_max(z->esq);  
        fprintf(stderr, "c\n");
        y_cor_orig = y->cor;
        
        x = y->esq;
        
        if(y->pai == z){
            if(x != NULL)
                x->pai = y;
        } else{
            transplant(t, y, y->esq);
            y->esq = z->esq;
            y->esq->pai = y;
        }
       
        transplant(t, z, y);
        y->dir = z->dir;
        y->dir->pai = y;
        y->cor = z->cor;
        // if(y->pai != z){
        //     fprintf(stderr, "d\n");
        //     if(y == y->pai->esq)
        //         y->pai->esq = x;
        //     else
        //         y->pai->dir = x;

        //     if (x != NULL)
        //         x->pai = y->pai;

        //     y->esq = z->esq;
        //     if(y->esq != NULL)
        //         y->esq->pai = y;
        // }
        // fprintf(stderr, "e\n");
        // if(z->pai == NULL)
        //     t->root = y;
        // else if(z == z->pai->esq)
        //     z->pai->esq = y;
        // else
        //     z->pai->dir = y;
        // fprintf(stderr, "f\n");
        // y->pai = z->pai;
        // y->dir = z->dir;
        // if(y->dir != NULL)
        //     y->dir->pai = y;
        // y->cor = z->cor;

        // if (y->pai == z && x != NULL)  
        //     x->pai = y;
    }


    if(y_cor_orig == BLACK)
        remover_fixup(t, x);

    free(z);
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
