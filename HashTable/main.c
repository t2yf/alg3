#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main(int argc, char *argv[]){
    struct hashTable *T = malloc(sizeof(struct hashTable));
    char op;
    int k;

    if(argc > 1){
        char *op = argv[1];

        if(strcmp(op, "-h") == 0){
            puts("Nome: ");
            puts("GRR: ");
            puts("login: ");

            puts("Nome: ");
            puts("GRR: ");
            puts("login: ");
        }
    } else {
        initialize_table(T);

        while(scanf(" %c %d", &op, &k) != EOF){
            if(op == 'i'){
                insert_hash(T, k);
            } else if (op == 'r') {
                delete_hash(T, k);
            }
        }

        print_hash(T);
        
    }

    destroy_table(T);

    return 0;
}