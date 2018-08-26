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
 */

#define MAX_PAGE_SIZE 65535 

#define HEADER_TYPE uint16_t
#define BYTE_TYPE uint8_t

typedef struct thirlage_page thirlage_page;

struct thirlage_page {
  BYTE_TYPE *bytes;
  HEADER_TYPE *p;
  HEADER_TYPE *number_of_rows; 
  HEADER_TYPE *positions_of_rows;    
};

void thirlage_init_page_from_bytes(thirlage_page *page, BYTE_TYPE *bytes);

int thirlage_insert_row_bytes_in_page(thirlage_page *page, BYTE_TYPE *bytes, size_t n);
