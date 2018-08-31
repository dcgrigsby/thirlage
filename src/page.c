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
  page->p = p;
  p += sizeof(*p);

  // set pointer to number_of_rows
  page->number_of_rows = (THIRLAGE_PAGE_HEADER_TYPE *)p;
  p += sizeof(*p);

  // set pointer to positions_of_rows
  page->positions_of_rows = page->number_of_rows + sizeof(THIRLAGE_PAGE_HEADER_TYPE);
}

/**
 * @brief Initialize an empty *page using its *bytes.
 */
void thirlage_init_empty_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, size_t s) {
	thirlage_init_page(page, bytes);
  *page->p = s;
  *page->number_of_rows = 0;
}

/**
 * @brief Insert a row's s *bytes in *page. Return 1 if successful; 0 if not.
 */
int thirlage_insert_row_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *row, size_t s) {
  // need to have enough room for the row *and* its positions_of_rows entry
  THIRLAGE_PAGE_HEADER_TYPE space_available = *page->p - (&page->positions_of_rows[*page->number_of_rows] - (THIRLAGE_PAGE_HEADER_TYPE *)page->bytes) - sizeof(THIRLAGE_PAGE_HEADER_TYPE);
  if (s > space_available) 
    return 0;

  // increment number of rows
  (*page->number_of_rows)++; 

  // copy row into page
  THIRLAGE_BYTE_TYPE *p = page->bytes + *page->p - s;
  memcpy(p, row, s); 

  // store position and move page->p
  *page->p = page->positions_of_rows[*page->number_of_rows - 1] = p - page->bytes; 

  return 1;
}

/**
 * @brief Set *row to the n-th in *page. Return 1 if successful; 0 if not.
 */
int thirlage_row_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE **row, THIRLAGE_PAGE_HEADER_TYPE n) {
  if (n > *page->number_of_rows - 1)
    return 0;

  *row = page->bytes + page->positions_of_rows[n]; 

  return 1;
}

/**
 * @brief Delete the s btyes of *row, the n-th in *page. 
 */
void thirlage_delete_row_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *row, THIRLAGE_PAGE_HEADER_TYPE n, size_t s) {
  // noting that rows are stored right to left, move s bytes to to the right all bytes from the left-most row until the one to be deleted
  THIRLAGE_BYTE_TYPE *src = page->bytes + page->positions_of_rows[*page->number_of_rows - 1];
  memmove(src + s, src, row - src); 

  // move page->p to correct position
  *page->p = *page->p + s;

  // decrement the number of rows
  (*page->number_of_rows)--;

  // shift all of the positions_for_rows up
  for (THIRLAGE_PAGE_HEADER_TYPE i = n; i < *page->number_of_rows - 1; i++)
    page->positions_of_rows[i] = page->positions_of_rows[i + 1];
}

