#include <stdio.h>

int proximo_id(void) {
    static int id = 0;
    id++;
    return id;
}

int main(void) {
    for (int i = 0; i < 5; i++) {
        printf("%d%c", proximo_id(), i < 4 ? ' ' : '\n');
    }
    return 0;
}
