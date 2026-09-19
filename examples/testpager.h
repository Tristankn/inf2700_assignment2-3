#ifndef _TESTPAGER_H_
#define _TESTPAGER_H_

extern void test_page_write(char const *fname);
extern void test_page_read(char const *fname);
extern void test_page_write_with_offset(char const *fname);
extern void test_page_read_with_offset(char const *fname);

#endif
