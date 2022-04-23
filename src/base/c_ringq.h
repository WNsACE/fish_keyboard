#ifndef __C_RINGQ_H__
#define __C_RINGQ_H__

#include "c_types_def.h"


BEGIN_C_DECLS


typedef enum _c_ringq_tag_t {
  C_RINGQ_TAG_NONE = 1 << 0,
  C_RINGQ_TAG_EMPTY = 1 << 1,
  C_RINGQ_TAG_FULL = 1 << 2,
} c_ringq_tag_t;

typedef struct _c_ringq_t {
  uint32_t head;
  uint32_t tail;
  uint32_t tag;
  void** data_list;
  uint32_t max_size;
} c_ringq_t;

c_ringq_t* c_ringq_init(c_ringq_t* ringq, void** data_list, uint32_t max_size);

c_bool_t c_ringq_is_full(c_ringq_t* ringq);

c_bool_t c_ringq_is_empty(c_ringq_t* ringq);

int32_t c_ringq_push(c_ringq_t* ringq, void* data);

void* c_ringq_pup(c_ringq_t* ringq);

void c_ringq_foreach(c_ringq_t* ringq, c_foreach_cb_t cb);

END_C_DECLS

#endif
