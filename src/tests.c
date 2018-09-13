#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "minunit.h"
#include "pager.h"
#include "file_header.h"
#include "page.h"

int tests_run = 0;
int assertions_evaluated = 0;

static char *test_pager() {
	thirlage_pager pager;

  FILE *file = fopen("test.thirlage", "a+");
  mu_assert("A database file can be opened for reading and appending", file != NULL); 

  mu_assert("A database file can be close", fclose(file) == 0);

  return 0;
}


static char *test_file_header() {
  const unsigned page_size = 512;
  thirlage_file_header file_header;
  char *bytes = malloc(page_size);
  char *p = bytes; 
  thirlage_init_empty_file_header(&file_header, &p, page_size);

  mu_assert("An empty file header should be valid", thirlage_validate_file_header(&file_header) == 0);
  // not testing identifier or version, since they're tested here^^^
  mu_assert("A file header should have the correct page size", *file_header.page_size == page_size);
  mu_assert("An empty file header should have zero pages", *file_header.number_of_pages == 0);
  mu_assert("A file header's size should be knowable", thirlage_file_header_size(&file_header));

  thirlage_page page;
  thirlage_init_empty_page(&page, p, TABLE_LEAF_PAGE, page_size - (p - bytes));
  mu_assert("A page that follows a header should start in the correct place", page.bytes != bytes);

  free(bytes);

  return 0;
}

static void print_page(thirlage_page *page, unsigned int page_size) {
  for (unsigned int i = 0; i < page_size; i++) {
    printf("%03u ", page->bytes[i]);
  }
  printf("\n");
}

static char *test_page() {
  const unsigned int page_size = 512;
  thirlage_page page;
  char bytes[page_size] = {0};
  thirlage_init_empty_page(&page, bytes, TABLE_LEAF_PAGE, page_size); 

  mu_assert("An page should have the correct type", *page.type == TABLE_LEAF_PAGE);
  mu_assert("An empty page's right_page_index should be 0", *page.right_page_index == 0);
  mu_assert("An empty page should have zero cells", *page.number_of_cells == 0);
  mu_assert("An empty page's write_index should point to the last byte of the page", *page.write_index = page_size);

  char cells[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  unsigned short cell_size = sizeof(cells[0]);
  unsigned short number_of_cells = sizeof(cells)/cell_size; 
  for (int i = 0; i < number_of_cells; i ++) {
      mu_assert("Adding a cell should succeed", thirlage_insert_cell_in_page(&page, cells[i], cell_size) == 0);
      mu_assert("Adding a cell should increase number_of_cells", *page.number_of_cells == i + 1);
      mu_assert("Adding a cell should move write_index appropriately", *page.write_index == page_size - *page.number_of_cells * cell_size);
  }

  char oversized_cell[1024] = {0};
  mu_assert("Adding an oversized cell should fail", thirlage_insert_cell_in_page(&page, oversized_cell, sizeof(oversized_cell)) != 0); 
 
  char *cell;
  for (int i = 0; i < number_of_cells; i ++) {
    mu_assert("Getting a cell should succeed", thirlage_cell_in_page(&page, &cell, i) == 0);
    mu_assert("A gotten cell should be correct", memcmp(cell, cells[i], cell_size) == 0);
  }

  mu_assert("Getting a cell that doesn't exist should fail", thirlage_cell_in_page(&page, &cell, *page.number_of_cells) != 0);

  unsigned short old_number_of_cells = *page.number_of_cells;
  unsigned short old_write_index = *page.write_index;
  thirlage_delete_cell_in_page(&page, cell, 1, cell_size);

  mu_assert("Deleting a cell should reduce the number of cells", *page.number_of_cells == old_number_of_cells - 1);
  mu_assert("Deleting a cell should move write_index appropriately", *page.write_index = old_write_index - cell_size);
  mu_assert("Should be able to get first cell after delete", thirlage_cell_in_page(&page, &cell, 0) == 0);
  mu_assert("A cell before the deleted should be correct", memcmp(cell, cells[0], cell_size) == 0);
  mu_assert("Should be able to get last cell after delete", thirlage_cell_in_page(&page, &cell, *page.number_of_cells - 1) == 0);
  mu_assert("A cell after the deleted should be correct", memcmp(cell, cells[number_of_cells - 2], cell_size) == 0);

  return 0;
}

static char *all_tests() {
  mu_run_test(test_pager);
  mu_run_test(test_file_header);
  mu_run_test(test_page);
  return 0;
}

int main(void) {
  char *result = all_tests();

  if (result != 0)
    printf("%s\n", result);
  else
    printf("All tests passed\n");

  printf("Tests run: %d\n", tests_run);
  printf("Assertions evaluated: %d\n", assertions_evaluated);

  return result != 0;
}
