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

/*
 * @brief Initialize an empty *page using its *bytes.
 */
void thirlage_init_empty_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, THIRLAGE_PAGE_HEADER_TYPE n) {
	thirlage_init_page(page, bytes);
  *page->p = n;
  *page->number_of_rows = 0;
}

/*
 * @brief Insert a row's n *bytes in *page.
 */
int thirlage_insert_row_bytes_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, size_t n) {
  // need to have enough room for the row *and* its positions_of_rows entry
  THIRLAGE_PAGE_HEADER_TYPE space_available = *page->p - (&page->positions_of_rows[*page->number_of_rows] - (THIRLAGE_PAGE_HEADER_TYPE *)page->bytes) - sizeof(THIRLAGE_PAGE_HEADER_TYPE);
  if (space_available < n) 
    return 0;

  // increment number of rows
  (*page->number_of_rows)++; 

  // copy bytes into page
  THIRLAGE_BYTE_TYPE *p = page->bytes + *page->p - n;
  memcpy(p, bytes, n); 

  // store position and move p
  *page->p = page->positions_of_rows[*page->number_of_rows - 1] = p - page->bytes; 

  return 1;
}

/*
 * @brief Set *bytes to the n-th row in *page.
 */
int thirlage_bytes_for_row_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE **bytes, THIRLAGE_PAGE_HEADER_TYPE n) {
  if (n > *page->number_of_rows - 1)
    return 0;

  *bytes = page->bytes + page->positions_of_rows[n]; 

  return 1;
}

void thirlage_delete_row_in_page(thirlage_page *page, THIRLAGE_PAGE_HEADER_TYPE n) {

}
