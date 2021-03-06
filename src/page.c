#include "page.h"
#include "string.h"

void thirlage_init_page(thirlage_page *page, char *bytes) {
  page->bytes = bytes;
  
  page->type = (unsigned short *)bytes;
  bytes += sizeof(page->type);

  page->right_page_index = (unsigned int *)bytes;
  bytes += sizeof(page->right_page_index);

  page->write_index = (unsigned short *)bytes;
  bytes += sizeof(page->write_index);

  page->number_of_cells = (unsigned short *)bytes;
  bytes += sizeof(page->number_of_cells);

  page->cells_indexes = (unsigned short *)bytes;
}

void thirlage_init_empty_page(thirlage_page *page, char *bytes, unsigned short page_type, size_t page_size) {
  thirlage_init_page(page, bytes);
  *page->type = page_type; 
  *page->right_page_index = 0;
  *page->write_index = page_size;
  *page->number_of_cells = 0;
}

int thirlage_insert_cell_in_page(thirlage_page *page, char *cell, size_t cell_size) {
  // include space of last cells_indexes by using number_of_cells and not number_of_cells - 1
  size_t space_available = *page->write_index - ((size_t *)page->cells_indexes + *page->number_of_cells - (size_t *)page->bytes); 

  // include space for new cells_indexes entry by including its sizeof
  size_t space_needed = cell_size + sizeof(*page->cells_indexes); 
  if (space_needed > space_available) 
    return -1;

  page->cells_indexes[*page->number_of_cells] = *page->write_index -= cell_size;
  
  memcpy(page->bytes + *page->write_index, cell, cell_size); 
  
  *page->number_of_cells += 1; 

  return 0;
}

int thirlage_cell_in_page(thirlage_page *page, char **cell, unsigned short cell_index) {
  if (cell_index > *page->number_of_cells - 1)
    return -1;

  *cell = page->bytes + page->cells_indexes[cell_index]; 

  return 0;
}

void thirlage_delete_cell_in_page(thirlage_page *page, char *cell, unsigned short cell_index, size_t cell_size) {
  *page->number_of_cells -= 1;

  for (unsigned short i = cell_index; i < *page->number_of_cells - 1; i++)
    page->cells_indexes[i] = page->cells_indexes[i + 1];

  *page->write_index = *page->write_index + cell_size;

  char *src = page->bytes + page->cells_indexes[*page->number_of_cells];
  char *dst = src + cell_size;
  memmove(dst, src, cell - src);
}

