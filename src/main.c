/**
 * @file
 * @copyright (c) 2020 - José A. García
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "include/arguments.h"

//! Indicador de celda ocupada
#define OCUPADO 1
//! Indicador de celda desocupada
#define VACIO 0
//! Indicador de celda visitada
#define SI 1
//! Indicador de celda no visitada
#define NO 0
//! Tamaño de red
#define N 25

/*
 * Prototipos
 */
//! Generador de números pseudo-aleatorios
float ran(void);

/**
 *
 * @param[in] i
 * @param[in] j
 * @return
 */
int Contador(unsigned int i, unsigned int j);

/**
 *
 * @param[in] nodo
 * @param[in] status
 * @return
 */
char Check(char nodo, char status);

/*
 * Variables globales
 */
char Nodos[N + 1][N + 1];   //!< Sistema percolante
char Status[N + 1][N + 1];  //!< Sistema visitado
//int Cluster[N * N + 1];     //!< Estadistica de clusteres

/**
 *
 * @param[in] argc
 * @param[in] argv
 * @return
 */
int main(int argc, char *argv[]) {
  long size;      //!< tamaño del sistema
  float prob;     //!< probabilidad inicial
  long *cluster;  //!< estadística de clústeres

  unsigned long i, j;  /* contadores */
  float rn;       /* random number */
  int Numero;     /* Numero de componentes en cada cluster */
  time_t tiempo;  /* semilla inicial para el generador */

  Arguments *arguments = arguments_read(argc, argv);
  if (arguments == NULL) {
    exit(1);
  }
  prob = arguments_getProbability(arguments);
  size = arguments_getLatticeSize(arguments);
  arguments_destroy(arguments);

  cluster = (long *) malloc((size * size + 1) * sizeof(long));

  /* Colocamos el sistema */
  srand((unsigned int) time(&tiempo));

  for (i = 1; i <= size; i++) {
    for (j = 1; j <= size; j++) {
      Status[i][j] = NO;
      rn = ran();
      if (rn <= prob) {
        Nodos[i][j] = OCUPADO;
      } else {
        Nodos[i][j] = VACIO;
      }
    }
  }

  /* Inicializamos el array de clusteres */
  for (i = 0; i <= size * size; i++) {
    cluster[i] = 0;
  }

  /* Muestra por pantalla la configuracion del sistema percolante */
  for (i = 1; i <= size; i++) {
    for (j = 1; j <= size; j++) {
      fprintf(stdout, "%c ", Nodos[i][j] * 10 + 32);
    }
    fprintf(stdout, "\n");
  }

  /* Contamos los clusteres */
  for (i = 1; i <= size; i++) {
    for (j = 1; j <= size; j++) {
      if (!Status[i][j] && Nodos[i][j]) {
        Status[i][j] = SI;
        Numero = Contador(i, j);
        cluster[Numero]++;
      } else if (!Nodos[i][j]) {
        cluster[0]++;
      }
    }
  }

  /* Sacamos la información de clusteres por pantalla */
  for (i = 0; i <= size * size; i++) {
    if (cluster[i] != 0) {
      fprintf(stdout, "# de clusteres de dimension %5ld: %ld\n", i, cluster[i]);
    }
  }

  for (i = size * size; i > 0; --i) {
    if (cluster[i]) {
      fprintf(stdout, "%f\t%f\t%ld\t%ld\t%ld\n", prob, (float) i / (size * size - cluster[0]), cluster[i], i,
              size * size - cluster[0]);
      break;
    }
  }

  free(cluster);

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
