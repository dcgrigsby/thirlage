#include <stddef.h>
#include <stdint.h>

/**
 *
 * @file page.h 
 * @brief Database Page struct and functions
 *
 * A page is a contiguous block of bytes containing a header and cells.
 *
 * The header starts at the first position of the bytes and is defined in the struct.
 *
 * Cells are variable length contiguous blocks of bytes stored in left-to-right order.  
 *
 * Cells hold either rows for a table, or nodes for an index.
 *
 * Cells are written starting at the end of the page, filling in right-to-left. 
 *
 * Pages can be no larger than 65535 bytes.
 *
 */

// header type capable of supporting page sizes up to 65535 bytes. attempts to set larger will be caught by compiler.
#define THIRLAGE_PAGE_HEADER_TYPE uint16_t
#define THIRLAGE_BYTE_TYPE uint8_t

typedef struct thirlage_page thirlage_page;

// TODO XXX page id, page type - init empty should require a page id, page type; right node page id 

struct thirlage_page {
  THIRLAGE_BYTE_TYPE *bytes;
  THIRLAGE_PAGE_HEADER_TYPE *write_index;
  THIRLAGE_PAGE_HEADER_TYPE *number_of_cells; 
  THIRLAGE_PAGE_HEADER_TYPE *cell_index;    
};

void thirlage_init_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes);

void thirlage_init_empty_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, size_t s);

int thirlage_insert_cell_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *cell, size_t s);

int thirlage_cell_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE **cell, THIRLAGE_PAGE_HEADER_TYPE n);

void thirlage_delete_cell_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *cell, THIRLAGE_PAGE_HEADER_TYPE n, size_t s);
