#include "ll.hh"
#include <cassert>

node* head = nullptr;

// Removes n from the list. 
// Assumes that n is a live object and a member of the list.
// Upon return, n is still a live object, but no longer a member of the list.
void erase(node* n) {
    (void) n; // Placeholder to avoid compiler warnings. Replace with your code!
}

// Adds n to the end of the list whose head is head. 
// Sets n->next and n->prev to the proper values. 
// Assumes that n is a live node and not already a member of the list.
void append(node* n) {
    node* prev = nullptr;
    node* trav = head;
    while (trav) {
        prev = trav;
        trav = trav->next;
    }
    n->prev = prev;
    n->next = nullptr;
    if (prev) {
        prev->next = n;
    } else {
        head = n;
    }
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
    // Code to test 'erase'
	check_list();

    node N1 = {1, nullptr, nullptr};
    node N2 = {2, nullptr, nullptr};
    node N3 = {3, nullptr, nullptr};
    append(&N1);
    append(&N2);
    append(&N3);
    check_list();

    erase(&N2);
    check_list();

    erase(&N3);
    check_list();

    erase(&N1);
    check_list();

    assert(head == nullptr);
}