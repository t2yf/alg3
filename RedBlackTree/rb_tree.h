#ifndef RBTREE
#define RBTREE

//Falta corrigir a parte de nível e cor

struct no_t {
    int chave;
    int cor;
    struct no_t *esq;
    struct no_t *dir;
    struct no_t *pai;
};

struct no_t *cria_no(int chave);
void inserir(struct no_t *r, int chave);
struct no_t *busca(struct no_t *r, int chave);
void inserir_fix(struct no_t **r, struct no_t *novo);
//inserir para consertar
    
//remover

//remover para consertar
    //rotacao para dir e esq
    //achar antecessor
void print_em_ordem(struct no_t *r);
void destroi_arvore(struct no_t *r);


#endif 