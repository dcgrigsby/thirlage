#define mu_assert(message, test) do { assertions_evaluated++; if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)
extern int tests_run;
extern int assertions_evaluated;
