#include "testschema.h"
#include "../src/pmsg.h"
#include "../src/schema.h"
#include "test_data_gen.h"
#include <string.h>

#define NUM_RECORDS 1000
#define DELETE_EVERY_N_TH 7

/* The records generated in test_tbl_write().
   Will be used in test_tbl_read() to check for correctness. */
record records[NUM_RECORDS];

/* The records inserted in test_tbl_write().
   Will be used in test_tbl_read() to check for correctness. */
int inserted[NUM_RECORDS];

void test_tbl_write(char const *tbl_name) {
  put_msg(INFO, "test_tbl_write (\"%s\") ...\n", tbl_name);

  open_db();
  /* put_pager_info(DEBUG, "After open_db"); */

  char id_attr[3] = "Id", str_attr[11] = "Str", int_attr[11] = "Int";
  char *attrs[] = {id_attr, strcat(str_attr, tbl_name), strcat(int_attr, tbl_name)};
  int attr_types[] = {INT_TYPE, STR_TYPE, INT_TYPE};
  schema_p sch = create_test_schema(tbl_name, 3, attrs, attr_types);
  tbl_p tbl = get_table(schema_name(sch));

  test_data_gen(sch, records, NUM_RECORDS);

  for (int rec_n = 0; rec_n < NUM_RECORDS; rec_n++) {
    /* printf("rec_n %d  ", rec_n); */
    insert_record(records[rec_n], sch);
    inserted[rec_n] = 1;
    /* for every n-th insertion, we delete an earlier inserted record
       near the middle of the file */
    if ((rec_n % DELETE_EVERY_N_TH) == DELETE_EVERY_N_TH - 1) {
      table_delete_records(tbl, id_attr, "=", rec_n / 2);
      inserted[rec_n / 2] = 0;
      /* put_msg(DEBUG, "record %d deleted.\n", rec_n / 2); */
    }
    /* put_pager_info(DEBUG, "After writing a record"); */
  }

  /* put_pager_info(DEBUG, "Before page_terminate"); */
  put_db_info(DEBUG);
  close_db();
  /* put_pager_info(DEBUG, "After close_db"); */

  put_pager_profiler_info(INFO);
  put_msg(INFO, "test_tbl_write() done.\n\n");
}

void test_tbl_read(char const *tbl_name) {
  record from_db[NUM_RECORDS];
  put_msg(INFO, "test_tbl_read (\"%s\") ...\n", tbl_name);

  open_db();
  /* put_pager_info(DEBUG, "After open_db"); */

  schema_p sch = get_schema(tbl_name);
  tbl_p tbl = get_table(tbl_name);
  char id_attr[3] = "Id";
  tbl_begin(tbl);
  int id = 0;

  while (!eot(tbl)) {
    record out_rec = new_record(sch);
    get_record(out_rec, sch);
    id = record_field_int_val(out_rec, id_attr, sch);
    /* put_record_info(DEBUG, out_rec, sch); */
    from_db[id] = out_rec;
  }

  for (int rec_n = 0; rec_n < NUM_RECORDS; rec_n++) {
    if (inserted[rec_n]) {
      if (!equal_record(from_db[rec_n], records[rec_n], sch)) {
        put_msg(FATAL, "test_tbl_read:\n");
        put_record_info(FATAL, from_db[rec_n], sch);
        put_msg(FATAL, "should be:\n");
        put_record_info(FATAL, records[rec_n], sch);
        exit(EXIT_FAILURE);
      }
      release_record(from_db[rec_n], sch);
    }

    release_record(records[rec_n], sch);
    /* put_pager_info(DEBUG, "After reading a record"); */
  }

  /* put_pager_info(DEBUG, "Before page_terminate"); */
  put_pager_profiler_info(INFO);
  close_db();
  /* put_pager_info(DEBUG, "After close_db"); */

  put_msg(INFO, "test_tbl_read() succeeds.\n");
}

void test_tbl_natural_join(char const *my_tbl, char const *yr_tbl) {
  put_msg(INFO, "test_tbl_natural_join (\"%s\", \"%s\") ...\n", my_tbl, yr_tbl);

  test_tbl_write(yr_tbl);

  open_db();

  tbl_p tbl_m = get_table(my_tbl);
  tbl_p tbl_y = get_table(yr_tbl);

  table_natural_join(tbl_m, tbl_y);

  put_db_info(DEBUG);
  close_db();
  /* put_pager_info(DEBUG, "After close_db"); */

  put_pager_profiler_info(INFO);
  put_msg(INFO, "test_tbl_natural_join() done.\n\n");
}
