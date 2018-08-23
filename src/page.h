#include <stdint.h>

/**
 *
 * A database page library that follows the [Minimalist C Libraries](https://nullprogram.com/blog/2018/06/10/) 
 * precepts of a minimizing the number of functions, no dynamic memory allocations, no I/O and, at most, one struct.
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

int deserializePage(unsigned char *serializedPage,Page *page);
int serializePage(Page *page,unsigned char *serializedPage);
