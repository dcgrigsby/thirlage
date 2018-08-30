#include <stddef.h>
#include <stdint.h>

/**
 *
 * @file page.h 
 * @brief Database Page struct and functions
 *
 * A page is a contiguous block of bytes containing a header and rows for a table.
 *
 * The header starts at the first position of the bytes and is defined in the struct.
 *
 * Rows are variable length contiguous blocks of bytes stored in left-to-right order.  
 *
 * Rows are written starting at the end of the page, filling in right-to-left. 
 *
 * Pages can be no larger than 65535 bytes.
 *
 */

// header type capable of supporting page sizes up to 65535 bytes. attempts to set larger will be caught by compiler.
#define THIRLAGE_PAGE_HEADER_TYPE uint16_t
#define THIRLAGE_BYTE_TYPE uint8_t

typedef struct thirlage_page thirlage_page;

struct thirlage_page {
  THIRLAGE_BYTE_TYPE *bytes;
  THIRLAGE_PAGE_HEADER_TYPE *p;
  THIRLAGE_PAGE_HEADER_TYPE *number_of_rows; 
  THIRLAGE_PAGE_HEADER_TYPE *positions_of_rows;    
};

void thirlage_init_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes);

void thirlage_init_empty_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, THIRLAGE_PAGE_HEADER_TYPE n);

int thirlage_insert_row_bytes_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, size_t n);
