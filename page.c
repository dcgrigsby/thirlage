#include <stdint.h>

/*
 *
 * First crack at a simple page:
 *
 * A single table
 * A page represents a table
 * Single page, on disk, in memory with cells
 *
 * Future:
 *  
 * Multiple pages, fixed size w/ free list
 *  Single table still; how to link to next page?
 *
 * Multiple tables
 *  First page a table that points to other tables
 *
 * Delete cells, then defragment
 *
 * Grow pages, instead of fixed size.
 *  Retain free list for dropped tables. Consult before creating new page. 
 *
 * Think about how to do partial updates/patches when writing to pages
 *
 */

#define MAX_PAGE_SIZE 65535

/**
 *
 * A database pager library that follows the [Minimalist C Libraries](https://nullprogram.com/blog/2018/06/10/) 
 * precepts of a minimizing the number of functions, no dynamic memory allocations, no I/O and, at most, one struct.
 * 
 * 
 * A page is a contiguous block of bytes that holds rows for a table.
 *
 * A page has cells. Cells are contiguous blocks of bytes that represent one row in left-to-right order.  
 *
 * Cells are written starting at the end of the page, filling in right-to-left.
 *
 */

typedef struct Page Page;
struct Page {
  uint16_t number_of_cells; 
  uint16_t last_free_block;     // the last, or right-most, free block; next added cell will end here
  uint16_t *cell_offsets;       // Page size cannot be >65535, so 2 byte int is large enough
  uint8_t *blocks;
};

int serializePage(Page *page, unsigned char *serializedPage) {
  uint8_t *data = {0};
}

int deserializePage(unsigned char *serializedPage, Page *page) {
}



