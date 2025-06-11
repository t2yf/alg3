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
    double tmp = (k*0.9 - floor(k*0.9));
    return (int)(floor(m * tmp ));
}

int search_hash(struct hashTable *T, int k, int *pos){
    int pos1 = h1(k);

    //Caso 1: Chave nao estah em T1
    if(T->T1[pos1].state == EMPTY){
        return -1;
    }

    //Caso 2: Chave estah em T1 
    if(T->T1[pos1].state == OCCUPIED && T->T1[pos1].k == k){
        *pos = pos1;
        return 1;
    } 
    //Caso 3: Chave estah em T2
    else{
        int pos2 = h2(k);
        if(T->T2[pos2].state == OCCUPIED && T->T2[pos2].k == k){
            *pos = pos2;
            return 2;
        }
    }

    return -1;
}

/*OBS: Nos testes nao ha caso de colisao em T2*/
void insert_hash(struct hashTable *T, int k){
    int pos1 = h1(k);

    //Inserção em T1
    if(T->T1[pos1].state == EMPTY || T->T1[pos1].state == EXCLUDED){
        T->T1[pos1].k = k;
        T->T1[pos1].state = OCCUPIED;
    } else{
        //Inserção em T2, caso haja colisão em T1 
        int current_k = T->T1[pos1].k;

        //Se tiver chaves duplicadas ou seja se k == current_k, não faz nada
        if(k != current_k){
            //Colocar valor mais antigo em T2
            int pos2 = h2(current_k);
            if(T->T2[pos2].state == EMPTY ){
                T->T2[pos2].k = current_k;
                T->T2[pos2].state = OCCUPIED;

                //T1 recebe o novo k
                T->T1[pos1].k = k;
            } 
        }
    }
}


void delete_hash(struct hashTable *T, int k){
    int pos;
    int table = search_hash(T, k, &pos);

    //Procurar em T2
    if(table == 2){
        if(T->T2[pos].state == OCCUPIED && T->T2[pos].k == k) {
            T->T2[pos].state = EMPTY;
        }
    } else if(table == 1) {
        if(T->T1[pos].state == OCCUPIED && T->T1[pos].k == k){
            T->T1[pos].state = EXCLUDED;
        }
    }
}


void selectionSort(struct no_print *v, int tam)
{
    int min;
    for(int i=0; i<tam -1; i++){
        min = i;
        for(int j=i+1; j<tam; j++){
            if(v[j].key < v[min].key)
                min = j;
        }
        //Trocar structs de lugar
        struct no_print tmp = v[min];
        v[min] = v[i];
        v[i] = tmp;
    }
}

void print_hash(struct hashTable *T){
    struct no_print n[2*m];
    
    int count = 0;

    //Preencher com valores das tabelas
    for(int i=0; i<m; i++){
        if(T->T1[i].state == OCCUPIED){
            n[count].key = T->T1[i].k;
            strcpy(n[count].table, "T1");
            n[count].pos = i;
            count++;
        }
        if(T->T2[i].state == OCCUPIED){
            n[count].key = T->T2[i].k;
            strcpy(n[count].table, "T2");
            n[count].pos = i;
            count++;
        }
    }
    
    //Ordenar pela chave
    selectionSort(n, count);

    //Imprimir
    for(int i=0; i<count; i++){
        printf("%d,%s,%d\n", n[i].key, n[i].table, n[i].pos);
    }
}

void *destroyTable(struct hashTable *T){
    free(T);
    return NULL;
}



