#include <cstdio>

int global = 0;

int* f(int) {
    return &global;
}

int main() {
    int* ptr = f(2);
    printf("%d\n", *ptr);
}
