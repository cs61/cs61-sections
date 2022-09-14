#include <cstdio>

int* f(int x) {
    return &x;
}

int main() {
    int* ptr = f(2);
    printf("%d\n", *ptr);
}
