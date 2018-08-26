#include <stdio.h>
#include "minunit.h"
#include "page.h"

int tests_run = 0;

static char *test_page() {
	const THIRLAGE_PAGE_HEADER_TYPE page_size = 512;

	thirlage_page page;
  THIRLAGE_BYTE_TYPE bytes[page_size] = {0};
	thirlage_init_empty_page(&page, &bytes[0], page_size); 

  mu_assert("An empty page should have zero rows", *page.number_of_rows == 0);

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

  return result != 0;
}
