#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define OCUPADO 1
#define VACIO 0
#define SI 1
#define NO 0
#define N 500

/*
 * Prototipos
 */
float ran(void);

int Contador(unsigned int i, unsigned int j);

char Check(char nodo, char status);

/*
 * Variables globales
 */
char Nodos[N + 1][N + 1];   /* Sistema percolante */
char Status[N + 1][N + 1];  /* Sistema visitado */
int Cluster[N * N + 1];     /* Estadistica de clusteres */

int main(int argc, char *argv[]) {
    unsigned i, j;  /* contadores */
    float p;        /* probabilidad inicial */
    float rn;       /* random number */
    int Numero;     /* Numero de componentes en cada cluster */
    time_t tiempo;  /* semilla inicial para el generador */

    if (argc < 2) {
        fprintf(stdout, "\aERROR: la linea de comandos es:\n");
        fprintf(stdout, "\t$perc <prob>\n");
        fprintf(stdout, "...saliendo...\n");
        exit(1);
    } else {
        p = atof(argv[1]);
    }

    /* Colocamos el sistema */
    srand((unsigned int) time(&tiempo));

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            Status[i][j] = NO;
            rn = ran();
            if (rn <= p) {
                Nodos[i][j] = OCUPADO;
            } else {
                Nodos[i][j] = VACIO;
            }
        }
    }

    /* Inicializamos el array de clusteres */
    for (i = 0; i <= N * N; i++) {
        Cluster[i] = 0;
    }

    /* Muestra por pantalla la configuracion del sistema percolante */
//    for (i = 1; i <= N; i++) {
//        for (j = 1; j <= N; j++) {
//            fprintf(stdout, "%c ", Nodos[i][j] * 10 + 32);
//        }
//        fprintf(stdout, "\n");
//    }

    /* Contamos los clusteres */
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            if (!Status[i][j] && Nodos[i][j]) {
                Status[i][j] = SI;
                Numero = Contador(i, j);
                Cluster[Numero]++;
            } else if (!Nodos[i][j]) {
                Cluster[0]++;
            }
        }
    }

    /* Sacamos la información de clusteres por pantalla */
//    for (i = 0; i <= N * N; i++) {
//        fprintf(stdout, "# de clusteres de dimension %d: %d\n", i, Cluster[i]);
//    }

    for (i = N * N; i > 0; --i) {
        if (Cluster[i]) {
            fprintf(stdout, "%f\t%f\t%d\t%d\t%d\n", p, (float) i / (N * N - Cluster[0]), Cluster[i], i,
                    N * N - Cluster[0]);
            break;
        }
    }

    return 0;
}

float ran(void) {
    float rn;

    rn = rand();

    return (rn / RAND_MAX);
}

int Contador(unsigned int i, unsigned int j) {
    int n = 1;

    /* vecino de la izquierda */
    if (j > 1) {
        /* Comprobamos que haya un vecino no visitado */
        if (Check(Nodos[i][j - 1], Status[i][j - 1])) {
            Status[i][j - 1] = SI;      // El vecino ha sido visitado
            n += Contador(i, j - 1); // Sumamos los elementos del cluster
        }
    }

    /* vecino de arriba */
    if (i > 1) {
        /* Comprobamos que haya un vecino no visitado */
        if (Check(Nodos[i - 1][j], Status[i - 1][j])) {
            Status[i - 1][j] = SI;      // El vecino ha sido visitado
            n += Contador(i - 1, j); // Sumamos los elementos del cluster
        }
    }

    /* vecino de la derecha */
    if (j < N) {
        /* Comprobamos que haya un vecino no visitado */
        if (Check(Nodos[i][j + 1], Status[i][j + 1])) {
            Status[i][j + 1] = SI;      // El vecino ha sido visitado
            n += Contador(i, j + 1); // Sumamos los elementos del cluster
        }
    }

    /* vecino de abajo */
    if (i < N) {
        /* Comprobamos que haya un vecino no visitado */
        if (Check(Nodos[i + 1][j], Status[i + 1][j])) {
            Status[i + 1][j] = SI;      // El vecino ha sido visitado
            n += Contador(i + 1, j); // Sumamos los elementos del cluster
        }
    }

    return n;
}

char Check(char nodo, char status) {
    char resultado;

    if (nodo == OCUPADO && status == NO) {
        resultado = 1;
    } else {
        resultado = 0;
    }

    return resultado;
}
