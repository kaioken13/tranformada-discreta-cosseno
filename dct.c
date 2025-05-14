#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592

// Funcao para calcular os alfas
float alfa(int k, int n) {
    if (k == 0) {
        return 1.0f / sqrtf((float)n);
    }
    return sqrtf(2.0f / (float)n);
}

int main() {
    int n;

    // Le a ordem da matriz
    //printf("Entre a ordem da matriz: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Erro: Entrada inválida para uma ordem da matriz.\n");
        return 1;
    }

    // Alocando memoria dinamicamente
    float **p_xy = (float **)malloc(n * sizeof(float *));
    if (p_xy == NULL) {
        printf("Erro: Alocacao de memoria falhou para as linhas da matriz.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        p_xy[i] = (float *)malloc(n * sizeof(float));
        if (p_xy[i] == NULL) {
            printf("Erro: Alocacao de memoria falhou para as colunas da matriz.\n");
            // Libera memoria alocada anteriormente
            for (int k = 0; k < i; k++) {
                free(p_xy[k]);
            }
            free(p_xy);
            return 1;
        }
    }

    // Le os elementos da matriz
    //printf("Entre os elementos da matriz:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%f", &p_xy[i][j]) != 1) {
                printf("Erro: Entrada invalida para o elemento da matriz na posicao [%d][%d].\n", i, j); 
                // Libera memoria alocada
                for (int k = 0; k < n; k++) {
                    free(p_xy[k]);
                }
                free(p_xy);
                return 1;
            }
        }
    }

    // Aloca memoria dinamicamente para a saida da matriz DCT
    float **g_ij = (float **)malloc(n * sizeof(float *));
    if (g_ij == NULL) {
        printf("Erro: Alocacao de memoria falhou para as linhas da matriz de saida.\n"); 
        for (int k = 0; k < n; k++) {
            free(p_xy[k]);
        }
        free(p_xy);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        g_ij[i] = (float *)malloc(n * sizeof(float));
        if (g_ij[i] == NULL) {
            printf("Erro: Alocacao de memoria falhou para as colunas da matriz de saida.\n"); 
            // Libera memoria alocada anteriormente g_ij and p_xy
            for (int k = 0; k < i; k++) {
                free(g_ij[k]);
            }
            free(g_ij);
            for (int k = 0; k < n; k++) {
                free(p_xy[k]);
            }
            free(p_xy);
            return 1;
        }
    }

    // Calcula a matriz DCT
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float sum_val = 0.0f;
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    float cos_y = cosf(((2.0f * y + 1.0f) * j * PI) / (2.0f * n));
                    float cos_x = cosf(((2.0f * x + 1.0f) * i * PI) / (2.0f * n));
                    sum_val += p_xy[x][y] * cos_y * cos_x;
                }
            }
            g_ij[i][j] = alfa(i, n) * alfa(j, n) * sum_val;
        }
    }

    // Imprime o resultado da matriz DCT
    //printf("\nMatriz DCT (G_ij):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%9.3f", g_ij[i][j]);
            if (j < n - 1) {
                printf(" "); // Adiciona espaco entre os numeros na linha, mas nao no ultimo
            }
        }
        printf("\n");
    }

    // Libera memoria alocada
    for (int i = 0; i < n; i++) {
        free(p_xy[i]);
        free(g_ij[i]);
    }
    free(p_xy);
    free(g_ij);

    return 0;
}

