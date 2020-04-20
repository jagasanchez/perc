/*
 * (c) 2020 - José A. García Sánchez
 */
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "include/def.h"

//! Global variable holding if there is a parsing error
static Boolean parse_error = FALSE;

//! Peso del argumento para el tamaño
#define WEIGHT_SIZE_PARAM 1
//! Peso del argumento para la probabilidad
#define WEIGHT_PROBABILITY_PARAM 2
//! Valor total de todos los pesos para los argumentos obligatorios
#define TOTAL_WEIGHT_MANDATORY_PARAMS WEIGHT_SIZE_PARAM + WEIGHT_PROBABILITY_PARAM

//! Array con indicadores de procesado de cada argumento obligatorio
static Boolean mandatoryArgumentsParsed[] = {FALSE, FALSE};

//! Estructura con los argumentos aceptados
typedef struct Arguments {
  unsigned latticeSize;  //!< Tamaño de la red
  double probability;    //!< Probabilidad de llenado
} Arguments;

//! Lista de opciones programadas que son aceptadas
static struct option LONG_OPTIONS[] = {
    {"size", required_argument, 0, 's'},
    {"prob", required_argument, 0, 'p'},
    {"help", no_argument, 0, 'h'}
};

//! Prints the help
static void printHelp() {
  fputs("Usage: perc [options]\n", stdout);
  fputs("Options:\n", stdout);
  fputs("  -p <prob>, --prob <prob>\t<prob> is the filling probability. It must be in the range [0,1]\n", stdout);
  fputs("  -s <size>, --size <size>\t<size> is the size of the rectangular lattice\n", stdout);
  fputs("  -h, --help\t\t\tThis help\n", stdout);
}

/**
 * @brief
 * @param[in] value
 * @return
 */
static int parseSize(const char *value) {
  char *next;
  const long val = strtol(value, &next, 10);

  if (next == value || *next != '\0') {
    parse_error = TRUE;
    fprintf(stderr, "Error when parsing size with value [%s]\n", value);
  }

  if (val <= 0) {
    parse_error = TRUE;
    fprintf(stderr, "Invalid value [%ld] for size. It must be positive\n", val);
  }

  return val;
}

/**
 * @brief
 * @param[in] value
 * @return
 */
static double parseProbability(const char *value) {
  char *next;
  const double val = strtod(value, &next);

  if (next == value || *next != '\0') {
    parse_error = TRUE;
    fprintf(stderr, "Error when parsing probability with value [%s]\n", value);
  }

  if (val < .0 || val > 1.0) {
    parse_error = TRUE;
    fprintf(stderr, "Invalid value [%f] for probability. It must be in the range [0, 1]\n", val);
  }

  return val;
}

void arguments_destroy(Arguments *arguments) {
  if (arguments == NULL) {
    return;
  }
  free(arguments);
}

Arguments *arguments_read(const int argc, char *argv[]) {
  int c;
  int optionIndex = 0;
  Arguments *arguments = NULL;
  unsigned int total_weighted_param = 0;

  arguments = (Arguments *) malloc(sizeof(Arguments));

  while ((c = getopt_long(argc, argv, "s:p:h", LONG_OPTIONS, &optionIndex)) != -1) {
    switch (c) {
      case 's':
        if (!mandatoryArgumentsParsed[0]) {
          arguments->latticeSize = parseSize(optarg);
          total_weighted_param += WEIGHT_SIZE_PARAM;
          mandatoryArgumentsParsed[0] = TRUE;
        }
        break;
      case 'p':
        if (!mandatoryArgumentsParsed[1]) {
          arguments->probability = parseProbability(optarg);
          total_weighted_param += WEIGHT_PROBABILITY_PARAM;
          mandatoryArgumentsParsed[1] = TRUE;
        }
        break;
      case 'h':printHelp();
        arguments_destroy(arguments);
        return NULL;
      default:arguments_destroy(arguments);
        fprintf(stderr, "argument %c not recognized", c);
        return NULL;
    }

    if (parse_error) {
      arguments_destroy(arguments);
      return NULL;
    }
  }

  if (total_weighted_param != TOTAL_WEIGHT_MANDATORY_PARAMS) {
    arguments_destroy(arguments);
    fputs("Please provide all mandatory arguments\n", stderr);
    printHelp();
    return NULL;
  }

  return arguments;
}

unsigned arguments_getLatticeSize(const Arguments *arguments) {
  return arguments->latticeSize;
}

double arguments_getProbability(const Arguments *arguments) {
  return arguments->probability;
}