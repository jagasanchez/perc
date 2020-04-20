/*
 * (c) 2020 - José A. García Sánchez
 */

#ifndef PERC_SRC_INCLUDE_ARGUMENTS_H_
#define PERC_SRC_INCLUDE_ARGUMENTS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup arguments Arguments
 * @brief Module to extract the arguments from command line and create an object
 * to be used through the program.
 * @{
 */
typedef struct Arguments Arguments;

/**
 * @brief Read the arguments from the command line.
 * @param[in] argc Number of arguments
 * @param[in] argv List of arguments given to the program
 * @return Object with the read arguments
 */
Arguments *arguments_read(const int argc, char *argv[]);

/**
 * @brief Destroy the arguments object, releasing its memory.
 * @param[in] arguments Object to be destroyed
 */
void arguments_destroy(Arguments *arguments);

unsigned arguments_latticeSize(const Arguments *arguments);
double arguments_probability(const Arguments *arguments);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif //PERC_SRC_INCLUDE_ARGUMENTS_H_
