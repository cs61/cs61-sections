#include <cstdio>
#include <cstring>

const char* f(int) {
    char* buf = new char[100];
    strcpy(buf, "example");
    return buf;
}

int main() {
    const char* s = f(2);
    delete[] s;
    printf("%s\n", s);
}
