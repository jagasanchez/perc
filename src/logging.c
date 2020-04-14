/*
 * (c) 2020 - José A. García Sánchez
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

static int (*logger)(const char *string, va_list args) = &vprintf;

void logging_log(const char *string, ...) {
  char *lineFeedString;
  size_t length;
  size_t size;

  va_list argp;
  va_start(argp, string);

  length = (strlen(string) + 2);
  size = length * sizeof(char);

  lineFeedString = (char *) malloc(size);
  memset(lineFeedString, 0, size);
  strcpy(lineFeedString, string);
  strcat(lineFeedString, "\n");

  logger(lineFeedString, argp);

  free(lineFeedString);

  va_end(argp);
}
