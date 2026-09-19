#include "handle_input_options.h"
#include "testschema.h"

int main(int argc, char *argv[]) {
  handle_test_options(argc, argv);

  char my_tbl[] = "Me";
  test_tbl_write(my_tbl);
  test_tbl_read(my_tbl);

  /* test_tbl_natural_join(my_tbl, "You"); */

  return (0);
}
