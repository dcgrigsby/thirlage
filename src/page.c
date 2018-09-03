#include "page.h"
#include "string.h"

/**
 *  @brief Initialize *page using using its *bytes.
 */
void thirlage_init_page(thirlage_page *page, u8 *bytes) {
  // set pointer to bytes[0]
  page->bytes = bytes;

  void *p = (u8 *)bytes;
  
  // set pointer to type
  page->type = p;
  p += sizeof(*page->type);

  // set pointer right_page_id
  page->right_page_id = p;
  p += sizeof(*page->right_page_id);

  // set pointer to write index
  page->write_index = p;
  p += sizeof(*page->write_index);

  // set pointer to number_of_cells
  page->number_of_cells = p;
  p += sizeof(*page->number_of_cells);

  // set pointer to cells_indexes[0]
  page->cells_indexes = p;
  // no need to advance pointer
}

/**
 * @brief Initialize an empty *page using its *bytes.
 */
void thirlage_init_empty_page(thirlage_page *page, u8 *bytes, u8 type, size_t size) {
	thirlage_init_page(page, bytes);
  *page->type = type; 
  // no need to set right_page_id
  *page->write_index = size;
  *page->number_of_cells = 0;
}

/**
 * @brief Insert a cell's size *bytes in *page. Return 1 if successful; 0 if not.
 */
int thirlage_insert_cell_in_page(thirlage_page *page, u8 *cell, size_t size) {
  // need to have enough room for the cell *and* its cells_indexes entry
  u16 space_available = *page->write_index - (&page->cells_indexes[*page->number_of_cells] - (u16 *)page->bytes) - sizeof(u16);
  if (size > space_available) 
    return 0;

  // increment number of cells
  (*page->number_of_cells)++; 

  // copy cell into page
  u8 *p = page->bytes + *page->write_index - size;
  memcpy(p, cell, size); 

  // store cell index and move page->write_index
  *page->write_index = page->cells_indexes[*page->number_of_cells - 1] = p - page->bytes; 

  return 1;
}

/**
 * @brief Set *cell to the index-th in *page. Return 1 if successful; 0 if not.
 */
int thirlage_cell_in_page(thirlage_page *page, u8 **cell, u16 index) {
  if (index > *page->number_of_cells - 1)
    return 0;

  *cell = page->bytes + page->cells_indexes[index]; 

  return 1;
}

/**
 * @brief Delete the size btyes of *cell, the index-th in *page. 
 */
void thirlage_delete_cell_in_page(thirlage_page *page, u8 *cell, u16 index, size_t size) {
  // noting that cells are stored right to left, move s bytes to to the right all bytes from the left-most cell until the one to be deleted
  u8 *src = page->bytes + page->cells_indexes[*page->number_of_cells - 1];
  memmove(src + size, src, cell - src); 

  // move page->write_index to correct position
  *page->write_index = *page->write_index + size;

  // decrement the number of cells
  (*page->number_of_cells)--;

  // shift all of the cells_indexes up
  for (u16 i = index; i < *page->number_of_cells - 1; i++)
    page->cells_indexes[i] = page->cells_indexes[i + 1];
}

