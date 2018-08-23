#include "page.h"

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

#define MAX_PAGE_SIZE 65535 // Placed in .c and not .h because this should not be user configurable



int serializePage(Page *page, unsigned char *serializedPage) {
  uint8_t *data = {0};
  return 1;
}

int deserializePage(unsigned char *serializedPage, Page *page) {
  return 1;
}



