#include <stdint.h>

/**
 *
 * @file page.h 
 * @brief Database Page struct and functions
 *
 * A database page library that follows the [Minimalist C Libraries](https://nullprogram.com/blog/2018/06/10/) princles
 * of a minimizing the number of (non-static) functions, no dynamic memory allocations, no I/O and, at most, one struct.
 * 
 * A page is a contiguous block of bytes that holds a header and rows for a table.
 *
 * The header starts at the first position of the bytes and is defined in the Page struct.
 *
 * Rows are variable length contiguous blocks of bytes stored in left-to-right order.  
 *
 * Rows are written starting at the end of the page, filling in right-to-left.
 *
 */

#define MAX_PAGE_SIZE 65535 

#define HEADER_TYPE uint16_t
#define BYTE_TYPE uint16_t

typedef struct Page Page;

struct Page {
  BYTE_TYPE *bytes;
  HEADER_TYPE *number_of_rows; 
  HEADER_TYPE *positions_of_rows;    
};

void initPageFromBytes(Page *page, BYTE_TYPE *bytes);
