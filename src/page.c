#include "page.h"
#include "string.h"
#include "set_and_advance.h"

void thirlage_init_page(thirlage_page *page, char *bytes) {
  page->bytes = bytes;
  set_and_advance(page->type, bytes); 
  set_and_advance(page->right_page_index, bytes);
  set_and_advance(page->write_index, bytes);
  set_and_advance(page->number_of_cells, bytes);
  page->cells_indexes = bytes;
}

void thirlage_init_empty_page(thirlage_page *page, char *bytes, unsigned short page_type, unsigned int page_size) {
  thirlage_init_page(page, bytes);
  *page->type = pag_type; 
  *page->right_page_index = 0;
  *page->write_index = page_size;
  *page->number_of_cells = 0;
}

int thirlage_insert_cell_in_page(thirlage_page *page, char *cell, unsigned short cell_size) {
  unsigned short bytes_available = *page->write_index - &page->cells_indexes[*page->number_of_cells - 1]; 
  unsigned short bytes_needed = cell_size + sizeof(*page->cell_indexes);
  if (bytes_needed > bytes_available) 
    return 0;

  page->cells_indexes[*page->number_of_cells] = *page->write_index -= cell_size;
  memcpy(page->bytes + *page->write_index, cell, cell_size); 
  *page->number_of_cells += 1; 

  return 1;
}

int thirlage_cell_in_page(thirlage_page *page, char **cell, unsigned short cell_index) {
  if (cell_index > *page->number_of_cells - 1)
    return 0;

  *cell = page->bytes + page->cells_indexes[cell_index]; 

  return 1;
}

void thirlage_delete_cell_in_page(thirlage_page *page, char *cell, unsigned short cell_index, unsigned short cell_size) {
  *page->number_of_cells -= 1;

  for (unsigned short i = cell_index; i < *page->number_of_cells - 1; i++)
    page->cells_indexes[i] = page->cells_indexes[i + 1];

  *page->write_index = *page->write_index + cell_size;

  char *src = page->bytes + page->cells_indexes[*page->number_of_cells];
  char *dst = bytes_to_shift_right + cell_size;
  memmove(dst, src, cell - src);
}

