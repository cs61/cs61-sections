#include <cctype>
#include <cstdio>
#include <cstring>

const char* hulk_players[] = {
    "RUFFALO",
    "BANA",
    "FERRIGNO",
    "MIYAUCHI"
};

void hulk_greeting(const char* name) {
    char uc_name[16];

    // make uppercase version of `name`
    for (size_t i = 0; name[i] != 0; ++i) {
        uc_name[i] = toupper(name[i]);
    }
    uc_name[strlen(name)] = 0;
    printf("HULK SAY HELLO TO %s\n", uc_name);

    // find player
    for (size_t i = 0; hulk_players[i] != nullptr; ++i) {
        if (strcmp(hulk_players[i], uc_name) == 0) {
            printf("YOU GOOD ACTOR\n");
            return;
        }
    }
    printf("YOU NO PLAY HULK! HULK SMASH\n");
}


int main(int argc, char* argv[]) {
    // Run `./hulk` to call `hulk_greeting("Ruffalo")`,
    // or `./hulk NAME` to call `hulk_greeting(NAME)`.
    if (argc > 1) {
        hulk_greeting(argv[1]);
    } else {
        hulk_greeting("Ruffalo");
    }
    return 0;
}
