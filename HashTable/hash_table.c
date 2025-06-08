#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hash_table.h"

struct no_print{
    int key;
    char table[3];
    int pos;
};

void initialize_table(struct hashTable *T){
    for(int i=0; i<m; i++){
        T->T1[i].state = EMPTY;
        T->T2[i].state = EMPTY;
    }
}

int h1(int k){
    return k % m;
}

int h2(int k){
    double tmp = k * 0.9 - floor(k * 0.9);
    return (int)(floor(m * tmp));
}
//TODO fazer search hash h1 e search hash h2
int search_hash(struct hashTable *T, int k){
    int pos1 = h1(k);

    //Caso 1: Chave nao estah em T1
    if(T->T1[pos1].state == EMPTY){
        return -1;
    }

    //Caso 2: Chave estah em T1 
    if(T->T1[pos1].state == OCCUPIED && T->T1[pos1].k == k){
        return pos1;
    } 
    //Caso 3: pos1 em T1 estah excluida
    else if(T->T1[pos1].state == EXCLUDED){
        int pos2 = h2(k);
        if(T->T2[pos2].state == OCCUPIED && T->T2[pos2].k == k){
            return pos2;
        }
    }
    return -1;
}

//TODO se pos1 estiver ocupado, pos2 também, o que fazer??
//TODO resolver caso do 4, 15, 59 do teste1
void insert_hash(struct hashTable *T, int k){
    int pos1 = h1(k);

    printf("Inserir k = %d pos1 = %d\n", k, pos1);

    //Inserção em T1
    if(T->T1[pos1].state == EMPTY || T->T1[pos1].state == EXCLUDED){

        printf("Inserir em h1\n");

        T->T1[pos1].k = k;
        T->T1[pos1].state = OCCUPIED;
    } else{
        //Inserção em T2 caso haja colisão em T1 
        int current_k = T->T1[pos1].k;

        //Se tiver chaves duplicadas ou seja se k == current_k, não faz nada
        if(k != current_k){
            int pos2 = h2(k);
            if(T->T2[pos2].state == EMPTY){

                printf("Inserir k %d em h2 pos2 = %d\n", k, pos2);

                T->T2[pos2].k = current_k;
                T->T2[pos2].state = OCCUPIED;

                printf("state 5 %d\n", T->T2[pos2].state);

                //T1 recebe o novo k
                T->T1[pos1].k = k;
                printf("Novo k %d pos1 %d\n", k, pos1);
            } else {
                // TODO NAO ESTAH ENTRANDO AQUI 
                //Se pos2 estiver ocupado
                pos2++;
                T->T2[pos2].k = current_k;
                T->T2[pos2].state = OCCUPIED;

                printf("Inserir pos2 repetido k %d em h2 pos2 = %d\n", k, pos2);

                //T1 recebe o novo k
                T->T1[pos1].k = k;
            }
        }

    }

}

void delete_hash(struct hashTable *T, int k){
    //TODO usar busca_hash e ver como diferenciar T1 e T2 
    //Se chave estiver em T2
    int pos2 = h2(k);

    //printf("Delete k %d\n", k);
    //printf("pos2 %d\n", pos2);

    //printf("%d\n\n", T->T2[5].k);

    //Considerar que pode estar um a frente
    if(T->T2[pos2].k == k || T->T2[pos2++].k == k){
        //Deixar vazia quer dizer que pode reescrever

       // printf("Delete h2 k %d pos2 %d\n", k, pos2);

        T->T2[pos2].state = EMPTY;
    }else{
        //Se chave estiver em T1
        int pos1 = h1(k);
        if(T->T1[pos1].k == k){
            //printf("Delete h2 k %d pos1 %d\n", k, pos1);
            T->T1[pos1].state = EXCLUDED;
        }
    }
}

void selectionSort(struct no_print **v, int tam)
{
    int min;
    for(int i=0; i<tam-1; i++){
        min = i;
        for(int j=i+1; j<tam; j++){
            if(v[j]->key < v[min]->key)
                min = j;
        }
        //Trocar structs de lugar
        struct no_print *tmp = v[min];
        v[min] = v[i];
        v[i] = tmp;
    }
}

void print_hash(struct hashTable *T){
    struct no_print **n;
    n = malloc(2 * m * sizeof(struct no_print *)); 

    int count = 0;
    // Percorrer tabelas
    for(int i=0; i<m; i++){
        // T1
        if(T->T1[i].state == OCCUPIED){
            n[count] = malloc(sizeof(struct no_print));
            n[count]->key = T->T1[i].k;
            strcpy(n[count]->table, "T1");
            n[count]->pos = i; 
            count++;
        }
        // T2
        if(T->T2[i].state == OCCUPIED){
            n[count] = malloc(sizeof(struct no_print));
            n[count]->key = T->T2[i].k;
            strcpy(n[count]->table, "T2");
            n[count]->pos = i; 
            count++;
        }
    }

    // Ordenar pela chave
    selectionSort(n, count);

    // Imprimir
    for(int i=0; i<count; i++){
        printf("%d,%s,%d\n", n[i]->key, n[i]->table, n[i]->pos);
    }

    // Liberar posições
    for(int i=0; i < count; i++){
        free(n[i]);
    }
    free(n); 
}

void destroy_table(struct hashTable *T){
    free(T);
}