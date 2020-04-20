/*
 * (c) 2020 - José A. García Sánchez
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct Arguments {
  unsigned latticeSize;  //!< Tamaño de la red
  double probability;    //!< Probabilidad de llenado
} Arguments;

void arguments_destroy(Arguments *arguments) {
  if (arguments == NULL) {
    return;
  }
  free(arguments);
}

Arguments *arguments_read(const int argc, const char *argv[]) {
  Arguments *arguments = NULL;

  arguments = (Arguments *) malloc(sizeof(Arguments));

  // TODO Parse command line arguments
  arguments->latticeSize = 500;
//  arguments->probability = .5;

  if (argc < 2) {
    fprintf(stdout, "\aERROR: la linea de comandos es:\n");
    fprintf(stdout, "\t$perc <prob>\n");
    fprintf(stdout, "...saliendo...\n");
    arguments_destroy(arguments);
    return NULL;
  }
  arguments->probability = atof(argv[1]);

  return arguments;
}

unsigned arguments_getLatticeSize(const Arguments *arguments) {
  return arguments->latticeSize;
}

double arguments_getProbability(const Arguments *arguments) {
  return arguments->probability;
}
