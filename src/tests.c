#include <stdio.h>
#include "minunit.h"
#include "page.h"

int tests_run = 0;

static char *test_mu() {
  mu_assert("arg!", 1 == 1);
  return 0;
}

static char *all_tests() {
  mu_run_test(test_mu);
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
