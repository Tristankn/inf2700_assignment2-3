/** @file freelist.h
 * @brief List of free space.
 * @author Weihai Yu
 *
 * Each table has a list of blocks (except the last one) with free
 * space for inserting new record(s).
 */

#ifndef _FREELIST_H_
#define _FREELIST_H_

#include "pmsg.h"
#include "schema.h"

typedef struct freelist *freelist_p;

/* for debugging */
extern void put_freelist_info(pmsg_level, freelist_p);

/* freelist API */
extern freelist_p make_freelist(schema_p);
extern void release_freelist(freelist_p);
/** set free space for a block, return free space in the block
   in number of available records.
 */
extern int set_free_space(freelist_p, int blk_nr, int free_in_record);
/** get a block in memory with free space.
 */
extern page_p get_free_page(freelist_p);
#endif
