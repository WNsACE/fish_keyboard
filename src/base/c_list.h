#ifndef __C_LIST_H__
#define __C_LIST_H__

#include "c_types_def.h"


BEGIN_C_DECLS

typedef void*(*c_list_node_create_t)(void* data);
typedef void(*c_list_node_destroy_t)(void* data);
typedef int(*c_list_node_compare_t)(void* a, void* b);

typedef struct _c_list_node_t {
  void* data;
  struct _c_list_node_t* next;
} c_list_node_t;

typedef struct _c_list_t {
  uint32_t size;
  c_list_node_t head;
  struct _c_list_node_t* tail;

  c_list_node_create_t list_node_create;
  c_list_node_compare_t list_node_compare;
  c_list_node_destroy_t list_node_destroy;
} c_list_t;


c_list_t* c_list_init(c_list_t* list, c_list_node_create_t list_node_create, c_list_node_destroy_t list_node_destroy, c_list_node_compare_t list_node_compare);
void c_list_deinit(c_list_t* list);

void c_list_remove(c_list_t* list, void* data);

void c_list_foreach(c_list_t* list, c_foreach_cb_t cb);

c_bool_t c_list_push_back(c_list_t* list, void* data);

c_bool_t c_list_push_front(c_list_t* list, void* data);



END_C_DECLS

#endif
