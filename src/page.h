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

typedef uint16_t u16;
typedef uint8_t u8;

enum {
  TABLE_LEAF_PAGE = 1
};

typedef struct thirlage_page thirlage_page;

// page type - init empty should require a page type 

struct thirlage_page {
  u8 *bytes; 
  u8 *type;
  u16 *right_page_id;
  u16 *write_index;
  u16 *number_of_cells; 
  u16 *cells_indexes; 
};

void thirlage_init_page(thirlage_page *page, u8 *bytes);

void thirlage_init_empty_page(thirlage_page *page, u8 *bytes, u8 type, size_t size);

int thirlage_insert_cell_in_page(thirlage_page *page, u8 *cell, size_t size);

int thirlage_cell_in_page(thirlage_page *page, u8 **cell, u16 index);

void thirlage_delete_cell_in_page(thirlage_page *page, u8 *cell, u16 index, size_t size);
