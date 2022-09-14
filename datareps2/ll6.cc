#include "ll.hh"

node* head = nullptr;

// Insert node `n` into the list immediately before node `before`.
// If `before == nullptr`, append `n` to the list.
void insert(node* before, node* n) {
    if (!before) {
        node* prev = head;
        while (prev->next != nullptr) {
            prev = prev->next;
        }
        n->prev = prev;
        n->next = nullptr;
        prev->next = n;
    } else {
        n->prev = before->prev;
        n->next = before;
        before->prev = n;
    }
}

int main() {
	// Your code here to test `insert`
}
