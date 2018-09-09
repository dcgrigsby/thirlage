/**
 *
 * @file page.h 
 * @brief Database Page struct and functions
 *
 * A page is a contiguous block of bytes containing a header and cells.
 *
 * The header starts at bytes[0] and is defined in the struct.
 *
 * Cells are variable length contiguous blocks of bytes.  
 *
 * Cells hold either rows for a table, or nodes for an index.
 *
 * Cells are written starting at the end of the page, filling in right-to-left. 
 *
 */

enum PAGE_TYPES {
  TABLE_INTERIOR_PAGE = 1,
  TABLE_LEAF_PAGE
};

typedef struct thirlage_page thirlage_page;

struct thirlage_page {
  char *bytes; 
  unsigned short *type;
  unsigned int *right_page_index;
  unsigned short *write_index;
  unsigned short *number_of_cells; 
  unsigned short *cells_indexes; 
};

/**
 *  @brief Initialize *page using using its *bytes.
 */
void thirlage_init_page(thirlage_page *page, char *bytes);

/**
 * @brief Initialize an empty *page, of page_type type, of page_size size, using its *bytes.
 */
void thirlage_init_empty_page(thirlage_page *page, char *bytes, unsigned short page_type, unsigned int page_size);

/**
 * @brief Insert *cell's cell_size bytes in *page. Return 1 if successful; 0 if not.
 */
int thirlage_insert_cell_in_page(thirlage_page *page, char *cell, unsigned short cell_size);

/**
 * @brief Set *cell to the cell_index-th cell in *page. Return 1 if successful; 0 if not.
 */
int thirlage_cell_in_page(thirlage_page *page, char **cell, unsigned short cell_index);

/**
 * @brief Delete the cell_size btyes of *cell, the cell_index-th in *page, defragmenting in the process. 
 */
void thirlage_delete_cell_in_page(thirlage_page *page, char *cell, unsigned short cell_index, unsigned short cell_size);
