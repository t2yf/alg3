#ifndef HT
#define HT

#define m 11
enum stateHash { EMPTY, EXCLUDED, OCCUPIED }; 

struct slotHash{
    int k;
    enum stateHash state;
};

struct hashTable{
    struct slotHash T1[m];
    struct slotHash T2[m];
};

int h1(int k);
int h2(int k);
void initialize_table(struct hashTable *T);
int search_hash(struct hashTable *T, int k);
void insert_hash(struct hashTable *T, int k);
void delete_hash(struct hashTable *T, int k);
void print_hash(struct hashTable *T);
void destroy_table(struct hashTable *T);

#endif 