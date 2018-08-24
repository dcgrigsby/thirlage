#include "page.h"
#include "string.h"

void thirlage_init_page_from_bytes(thirlage_page *page, BYTE_TYPE *bytes) {
  // set pointer to bytes
  page->bytes = bytes;

  // set pointer to number_of_rows
  page->number_of_rows = (HEADER_TYPE *)bytes;

  // set pointer to positions_positions_of_rows
  page->positions_of_rows = (HEADER_TYPE *)bytes + sizeof(HEADER_TYPE);
}

void thirlage_insert_row_bytes_in_page(thirlage_page *page, BYTE_TYPE *bytes, size_t n) {
  // copy bytes into page
  HEADER_TYPE position_of_last_row = page->positions_of_rows[*page->number_of_rows - 1]; 
  BYTE_TYPE *p = page->bytes + position_of_last_row - n;
  memcpy(p, bytes, n); 

  // store position
  page->positions_of_rows[*page->number_of_rows] = p - page->bytes;

  // increment number of rows
  (*page->number_of_rows)++; 
}
