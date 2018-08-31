#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "page.h"

int tests_run = 0;
int assertions_evaluated = 0;

static void print_page(thirlage_page *page, size_t s) {
  for (int i = 0; i < s; i++) {
    printf("%03u ", page->bytes[i]);
  }
  printf("\n");
}

static char *test_page() {
	const size_t page_size = 512;
	thirlage_page page;
  THIRLAGE_BYTE_TYPE bytes[page_size] = {0};
	thirlage_init_empty_page(&page, bytes, page_size); 
  mu_assert("An empty page should have zero rows", *page.number_of_rows == 0);
  mu_assert("An empty page's p should point to the last byte of the page", *page.p = page_size);

  THIRLAGE_BYTE_TYPE rows[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  static size_t s = sizeof(rows[0]);

  for (int i = 0; i < s; i ++) {
      mu_assert("Adding a row should succeed", thirlage_insert_row_in_page(&page, rows[i], s) == 1);
      mu_assert("Adding a row should increase number_of_rows", *page.number_of_rows == i + 1);
      mu_assert("Adding a row should move p appropriately", *page.p == page_size - *page.number_of_rows * s);
  }

  THIRLAGE_BYTE_TYPE oversized_row[1024] = {0};
  mu_assert("Adding an oversized row should fail", thirlage_insert_row_in_page(&page, oversized_row, sizeof(oversized_row)) == 0); 
 
  THIRLAGE_BYTE_TYPE *row_p;
  for (int i = 0; i < s; i ++) {
    mu_assert("Getting a row should succeed", thirlage_row_in_page(&page, &row_p, i) == 1);
    mu_assert("A gotten row should be correct", memcmp(row_p, rows[i], s) == 0);
  }

  mu_assert("Getting a row that doesn't exist should fail", thirlage_row_in_page(&page, &row_p, *page.number_of_rows) == 0);

   
  THIRLAGE_PAGE_HEADER_TYPE n = *page.number_of_rows;
  THIRLAGE_PAGE_HEADER_TYPE p = *page.p;
  thirlage_delete_row_in_page(&page, row_p, 1, s);
  mu_assert("Deleting a row should reduce the number of rows", *page.number_of_rows == n - 1);
  mu_assert("Deleting a row should move p appropriately", *page.p = p - s);
  thirlage_row_in_page(&page, &row_p, 0);
  mu_assert("A row before the deleted should be correct after the deleted", memcmp(row_p, rows[0], s) == 0);
  thirlage_row_in_page(&page, &row_p, *page.number_of_rows - 1);
  mu_assert("A row after the deleted should be correct after the deleted", memcmp(row_p, rows[s - 1], s) == 0);

  return 0;
}

static char *all_tests() {
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
