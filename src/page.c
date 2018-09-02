#include "page.h"
#include "string.h"

/**
 *  @brief Initialize *page using using its *bytes.
 */
void thirlage_init_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes) {
  // set pointer to bytes
  page->bytes = bytes;

  THIRLAGE_PAGE_HEADER_TYPE *p = (THIRLAGE_PAGE_HEADER_TYPE *)bytes;

  // set pointer p;
  page->write_index = p;
  p += sizeof(*p);

  // set pointer to number_of_cells
  page->number_of_cells = (THIRLAGE_PAGE_HEADER_TYPE *)p;
  p += sizeof(*p);

  // set pointer to cell_index[0]
  page->cell_index = p;
}

/**
 * @brief Initialize an empty *page using its *bytes.
 */
void thirlage_init_empty_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, size_t s) {
	thirlage_init_page(page, bytes);
  *page->write_index = s;
  *page->number_of_cells = 0;
}

/**
 * @brief Insert a cell's s *bytes in *page. Return 1 if successful; 0 if not.
 */
int thirlage_insert_cell_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *cell, size_t s) {
  // need to have enough room for the cell *and* its cell_index entry
  THIRLAGE_PAGE_HEADER_TYPE space_available = *page->write_index - (&page->cell_index[*page->number_of_cells] - (THIRLAGE_PAGE_HEADER_TYPE *)page->bytes) - sizeof(THIRLAGE_PAGE_HEADER_TYPE);
  if (s > space_available) 
    return 0;

  // increment number of cells
  (*page->number_of_cells)++; 

  // copy cell into page
  THIRLAGE_BYTE_TYPE *p = page->bytes + *page->write_index - s;
  memcpy(p, cell, s); 

  // store cell index and move page->write_index
  *page->write_index = page->cell_index[*page->number_of_cells - 1] = p - page->bytes; 

  return 1;
}

/**
 * @brief Set *cell to the n-th in *page. Return 1 if successful; 0 if not.
 */
int thirlage_cell_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE **cell, THIRLAGE_PAGE_HEADER_TYPE n) {
  if (n > *page->number_of_cells - 1)
    return 0;

  *cell = page->bytes + page->cell_index[n]; 

  return 1;
}

/**
 * @brief Delete the s btyes of *cell, the n-th in *page. 
 */
void thirlage_delete_cell_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *cell, THIRLAGE_PAGE_HEADER_TYPE n, size_t s) {
  // noting that cells are stored right to left, move s bytes to to the right all bytes from the left-most cell until the one to be deleted
  THIRLAGE_BYTE_TYPE *src = page->bytes + page->cell_index[*page->number_of_cells - 1];
  memmove(src + s, src, cell - src); 

  // move page->write_index to correct position
  *page->write_index = *page->write_index + s;

  // decrement the number of cells
  (*page->number_of_cells)--;

  // shift all of the cell_indexs up
  for (THIRLAGE_PAGE_HEADER_TYPE i = n; i < *page->number_of_cells - 1; i++)
    page->cell_index[i] = page->cell_index[i + 1];
}

