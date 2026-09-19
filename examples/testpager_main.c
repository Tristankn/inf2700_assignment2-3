#include "handle_input_options.h"
#include "testpager.h"

int main(int argc, char *argv[]) {
  handle_test_options(argc, argv);

  test_page_write("testpage");
  test_page_read("testpage");

  test_page_write_with_offset("testpage_w_offset");
  test_page_read_with_offset("testpage_w_offset");

  return (0);
}
