#include <cstdio>

const char* f(int) {
    char buf[100] = "example";
    return buf;
}

int main() {
    printf("%p\n", f(2));
}
