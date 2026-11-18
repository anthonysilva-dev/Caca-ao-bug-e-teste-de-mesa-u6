#include <stdio.h>
#include <stdlib.h>

int *cria_sequencia(int n) {
    int *v = malloc(n * sizeof(int));
    if (v == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        v[i] = i + 1;
    }
    return v;
}

int main(void) {
    int n = 5;
    int *seq = cria_sequencia(n);
    if (seq == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d%c", seq[i], i < n - 1 ? ' ' : '\n');
    }

    free(seq);
    return 0;
}
