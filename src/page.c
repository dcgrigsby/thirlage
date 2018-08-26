#include "page.h"
#include "string.h"

void thirlage_init_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes) {
  THIRLAGE_BYTE_TYPE *p = bytes;

  // set pointer to bytes
  page->bytes = p;
  p += sizeof(THIRLAGE_PAGE_HEADER_TYPE);

  // set pointer p;
  page->p = (THIRLAGE_PAGE_HEADER_TYPE *)p;
  p += sizeof(THIRLAGE_PAGE_HEADER_TYPE);

  // set pointer to number_of_rows
  page->number_of_rows = (THIRLAGE_PAGE_HEADER_TYPE *)p;
  p += sizeof(THIRLAGE_PAGE_HEADER_TYPE);

  // set pointer to positions_of_rows
  page->positions_of_rows = page->number_of_rows + sizeof(THIRLAGE_PAGE_HEADER_TYPE);
}

void thirlage_init_empty_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, size_t n) {
	thirlage_init_page(page, bytes);
	*page->p = n - 1;
  *page->number_of_rows = 0;
}

int thirlage_insert_row_bytes_in_page(thirlage_page *page, THIRLAGE_BYTE_TYPE *bytes, size_t n) {

  /*
  // calculate available space, if n > available_space then return 0

  // copy bytes into page
  HEADER_TYPE position_of_last_row = page->positions_of_rows[*page->number_of_rows - 1]; 
  BYTE_TYPE *p = page->bytes + page->p - n;
  memcpy(p, bytes, n); 

  // increment number of rows
  (*page->number_of_rows)++; 

  HEADER_TYPE position = p - page->bytes;

  // store position
  page->positions_of_rows[*page->number_of_rows - 1] = position;

  // update the page pointer
  page->p = position - 1;
  */

  return 1;
}


