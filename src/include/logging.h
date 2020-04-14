/*
 * (c) 2020 - José A. García Sánchez
 */

#ifndef PERC_SRC_INCLUDE_LOGGING_H_
#define PERC_SRC_INCLUDE_LOGGING_H_

/**
 * @defgroup logging Logging
 * @brief Logging functionality to write messages to standard output.
 * @{
 */

/**
 * @brief Writes a formatted message to output.
 *
 * @param[in] string Formatted message to be written
 * @param ... Addtional values to be put in the formatted message
 */
void logging_log(const char *string, ...);

/**
 * @}
 */
#endif //PERC_SRC_INCLUDE_LOGGING_H_
