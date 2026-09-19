/** @file test_data_gen.h
 *  @brief Test data generator
 *  @author Weihai Yu
 */

#ifndef _TEST_DATA_GEN_H_
#define _TEST_DATA_GEN_H_

#include "../src/schema.h"

/** create the test schema
my_schema (MyIdField: int, MyStrField:str[TEST_STR_LEN], myIntField:int) */
extern schema_p create_test_schema(char const *name, int n_attrs, char *attrs[],
                                   int attr_types[]);
/** resets the test data generator.
generate @em n records.
*/
extern void test_data_gen(schema_p sch, record *r, int n);

/** fill a record with some generated data. */
extern void fill_gen_record(schema_p s, record r, int id);

#endif
