#pragma once

#include <stddef.h>

/**
 *
 * @file file_header.h
 * @brief Database File Header stuct and functions
 *
 * The header holds database file meta data.
 *
 * It is stored starting at the first byte of the database file.
 *
 * The first page follows; it is shortened the length of the header.
 *
 */

#define FILE_HEADER_IDENTIFIER "thirlage"
#define FILE_HEADER_VERSION 1

typedef struct thirlage_file_header thirlage_file_header;

struct thirlage_file_header {
  char *identifier;
  unsigned short *version;
  unsigned int *page_size;
  unsigned int *number_of_pages;
};

/**
 * @brief Initialize *file_header using its *bytes, advancing **bytes forward so that a page can follow.
 */
void thirlage_init_file_header(thirlage_file_header *file_header, char **bytes);

/**
 * @brief Initialize an empty *file_header using its *bytes with a page_size pages.
 */
void thirlage_init_empty_file_header(thirlage_file_header *file_header, char **bytes, size_t page_size);

/**
 * @brief Validate *file_header, returning 1 if valid; 0 if not.
 */
int thirlage_validate_file_header(thirlage_file_header *file_header);

/**
 * @brief Return the size of the header in bytes
 */
size_t thirlage_file_header_size(thirlage_file_header *file_header);
