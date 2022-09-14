#ifndef DATAREPS2_LL_HH
#define DATAREPS2_LL_HH

struct node {
	int value;
	node* prev;
	node* next;
};

extern node* head;

inline node* find(int v) {
    node* trav = head;
    while (trav && trav->value != v) {
        trav = trav->next;
    }
    return trav;
}

#endif
