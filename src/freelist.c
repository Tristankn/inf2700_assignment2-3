/**************************************************************
 * Free list for assignments in the Databases course INF-2700 *
 * UIT - The Arctic University of Norway                      *
 * Author: Weihai Yu                                          *
 **************************************************************/

#include "freelist.h"
#include "pager.h"
#include "pmsg.h"
#include "schema.h"

typedef struct elm *elm_p;

/** @brief element in list */
typedef struct elm {
  int blk_nr;    /**< block number */
  int available; /**<  free space avaiable, number of records */
  elm_p next;    /**< next element in list */
} elm;

/** @brief free list */
typedef struct freelist {
  schema_p sch;        /**< schema of the table */
  elm_p head;          /**< first element */
  int available_total; /**< total free space avaiable, in number of records */
} freelist;

void put_freelist_info(pmsg_level level, freelist_p fl) {
  if (!fl) {
    put_msg(level, "NULL free list\n");
    return;
  }
  if (fl->available_total == 0) {
    put_msg(level, "Table %s has no free space\n", schema_name(fl->sch));
    return;
  }
  put_msg(level, "Table %s has free space for %d records\n",
          schema_name(fl->sch), fl->available_total);
  elm_p elm = fl->head;
  while (elm) {
    append_msg(level, "  %d(%d),", elm->blk_nr, elm->available);
    elm = elm->next;
  }
  append_msg(level, "\n");
}

freelist_p make_freelist(schema_p sch) {
  freelist_p fl = malloc(sizeof(freelist));
  fl->sch = sch;
  fl->head = 0;
  fl->available_total = 0;
  return fl;
}

void release_freelist(freelist_p fl) {
  if (!fl)
    return;
  elm_p nextelm = fl->head;
  elm_p elm;
  while (nextelm) {
    elm = nextelm;
    nextelm = elm->next;
    free(elm);
  }
  free(fl);
  fl = 0;
}

static elm_p make_elm(int blk_nr, int free_in_records) {
  elm_p elm = malloc(sizeof(elm));
  elm->blk_nr = blk_nr;
  elm->available = free_in_records;
  elm->next = 0;
  return elm;
}

static void insert_elm(freelist_p fl, elm_p elm, elm_p elm_prev) {
  if (elm_prev) {
    elm->next = elm_prev->next;
    elm_prev->next = elm;
  } else {
    elm->next = fl->head;
    fl->head = elm;
  }
}

static void delete_elm(freelist_p fl, elm_p elm, elm_p elm_prev) {
  if (elm_prev)
    elm_prev->next = elm->next;
  else
    fl->head = elm->next;
  free(elm);
}

int set_free_space(freelist_p fl, int blk_nr, int free_in_records) {
  if (!fl || (blk_nr == (file_num_blocks(schema_name(fl->sch)) - 1)))
    return 0;

  elm_p elm = fl->head;
  elm_p elm_prev = 0;
  while (elm) {
    if (elm->blk_nr == blk_nr) {
      if (free_in_records == 0) {
        fl->available_total -= elm->available;
        delete_elm(fl, elm, elm_prev);
      } else {
        fl->available_total += free_in_records - elm->available;
        elm->available = free_in_records;
      }
      return free_in_records;
    }
    if (elm->blk_nr > blk_nr) {
      if (free_in_records > 0) {
        fl->available_total += free_in_records;
        insert_elm(fl, make_elm(blk_nr, free_in_records), elm_prev);
      }
      return free_in_records;
    }
    elm_prev = elm;
    elm = elm->next;
  }
  fl->available_total += free_in_records;
  insert_elm(fl, make_elm(blk_nr, free_in_records), elm_prev);
  return free_in_records;
}

page_p get_free_page(freelist_p fl) {
  if (!fl)
    return 0;

  for (elm_p elm = fl->head; elm; elm = elm->next) {
    page_p p_in_mem = file_block_page(schema_name(fl->sch), elm->blk_nr);
    if (p_in_mem)
      return p_in_mem;
  }
  return 0;
}
