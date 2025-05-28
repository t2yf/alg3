#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main(int argc, char *argv[]){

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
        puts(":(");
    }

    return 0;
}