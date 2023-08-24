#include "ll.hh"
#include <cassert>

node* head = nullptr;

// Adds n to the end of the list whose head is head. 
// Sets n->next and n->prev to the proper values. 
// Assumes that n is a live node and not already a member of the list.
void append(node* n) {
    (void) n; // Placeholder to avoid compiler warnings. Replace with your code!
}

// representation checker
void check_list() {
    node* prev = nullptr;
    node* trav = head;
    while (trav) {
        assert(trav->prev == prev);
        prev = trav;
        trav = trav->next;
    }
}

int main() {
    // Code to test 'append'
	check_list();

    node N1 = {1, nullptr, nullptr};
    append(&N1);
    check_list();
    assert(head != nullptr);

    node N2 = {2, nullptr, nullptr};
    append(&N2);
    check_list();
    assert(head != nullptr);
}