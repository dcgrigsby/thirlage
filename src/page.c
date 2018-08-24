#include "page.h"

void initPageFromBytes(Page *page, BYTE_TYPE *bytes) {
  page->bytes = page->number_of_rows = bytes;
  page->positions_of_rows = bytes + sizeof(HEADER_TYPE);
}

