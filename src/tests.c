#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "page.h"

int tests_run = 0;
int assertions_evaluated = 0;

static char *test_page() {
	const THIRLAGE_PAGE_HEADER_TYPE page_size = 512;
	thirlage_page page;
  THIRLAGE_BYTE_TYPE bytes[page_size] = {0};
	thirlage_init_empty_page(&page, bytes, page_size); 
  mu_assert("An empty page should have zero rows", *page.number_of_rows == 0);
  mu_assert("An empty page's p should point to the last byte of the page", *page.p = page_size);

  THIRLAGE_BYTE_TYPE row[] = {3, 2, 1};
  mu_assert("Adding a row should succeed", thirlage_insert_row_bytes_in_page(&page, row, sizeof(row)) == 1);
  mu_assert("Adding a row should increase number_of_rows", *page.number_of_rows == 1);
  mu_assert("Adding a row should move p appropriately", *page.p == page_size - sizeof(row));

  THIRLAGE_BYTE_TYPE *row_bytes = thirlage_bytes_for_row_in_page(&page, 0);
  mu_assert("*row_bytes should be correct", memcmp(row_bytes, row, sizeof(row)) == 0);


  THIRLAGE_BYTE_TYPE oversized_row[1024] = {0};
  mu_assert("Adding an oversized row should fail", thirlage_insert_row_bytes_in_page(&page, oversized_row, sizeof(oversized_row)) == 0); 

  /*
  for (int i = 0; i < 512; i++) {
    printf("%u ", page.bytes[i]);
  }
  printf("\n");
  */

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
