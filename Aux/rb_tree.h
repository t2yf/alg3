#ifndef RBTREE
#define RBTREE

struct no_t {
    int chave;
    char cor;
    struct no_t *esq;
    struct no_t *dir;
    struct no_t *pai;
};

struct tree_t{
    struct no_t *root;
    struct no_t *nil;
};

struct tree_t *cria_arvore();
struct no_t *cria_no(struct tree_t *t, int chave);
void inserir(struct tree_t *t, int chave);
void remover(struct tree_t *t, int chave);
void print_em_ordem(struct tree_t *t);
void destroi(struct tree_t *t);

#endif 