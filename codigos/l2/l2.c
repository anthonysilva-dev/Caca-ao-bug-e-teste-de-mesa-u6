#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    double *notas, soma = 0.0;

    printf("Quantas notas? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    notas = malloc(n * sizeof(double));
    if (notas == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%lf", &notas[i]);
        soma += notas[i];
    }

    printf("Media: %.2f\n", soma / n);

    free(notas);
    return 0;
}
