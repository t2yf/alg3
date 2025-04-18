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

struct tree_t{
    struct no_t *root;
};

struct tree_t *cria_arvore(int chave);
struct no_t *cria_no(int chave);
void inserir(struct tree_t *t, int chave);
void remover(struct tree_t *t, int chave);
void print_em_ordem(struct tree_t *t);
void destroi(struct tree_t *t);



#endif 