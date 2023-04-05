#ifndef __C_FIXED_LIST_H__
#define __C_FIXED_LIST_H__

#include "c_types_def.h"

BEGIN_C_DECLS

typedef struct _c_fixed_list_node_t c_fixed_list_node_t;

typedef int(*c_fixed_list_compare_t)(void* a, void* b);

#pragma pack(push, 1)

struct _c_fixed_list_node_t {
  int32_t curr;
  c_fixed_list_node_t* next;
};

typedef struct _c_fixed_list_t {
  uint32_t size;
  uint32_t type_size;

  uint8_t* p_fixed_mem_data;
  c_bool_t* p_fixed_free_mem_data;
  c_fixed_list_node_t* p_fixed_mem_node;

  c_fixed_list_compare_t compare;

  uint32_t cursor;
  uint32_t capacity;
  c_fixed_list_node_t* head;
} c_fixed_list_t;

#define C_FIXED_LIST_DEFINE(type, size)                               \
typedef struct _c_fixed_list_##type {                                 \
  c_fixed_list_t base;                                                \
  type fixed_mem_data[size];                                          \
  c_bool_t fixed_free_mem_data[size];                                 \
  c_fixed_list_node_t fixed_mem_node[size];                           \
} c_fixed_list_##type;

#pragma pack(pop)

#define C_FIXED_LIST_TYPE_T(type) c_fixed_list_##type

#define C_FIXED_LIST_GET_TYPE_SIZE(type) sizeof(C_FIXED_LIST_TYPE_T(type))

#define C_FIXED_LIST_GET_FIXED_MEN_SIZE(list)  ARRAY_SIZE((list)->fixed_mem)

c_fixed_list_t* c_fixed_list_init(c_fixed_list_t* list, uint32_t size, uint32_t fixed_size, uint32_t type_size, c_fixed_list_compare_t compare);

void c_fixed_list_deinit(c_fixed_list_t* list);

c_bool_t c_fixed_list_remove(c_fixed_list_t* list, void* data);

void c_fixed_list_foreach(c_fixed_list_t* list, c_foreach_cb_t cb, void* ctx);

c_bool_t c_fixed_list_push_back(c_fixed_list_t* list, void* data);

c_bool_t c_fixed_list_sorted_insert(c_fixed_list_t* list, void* data);

c_bool_t c_fixed_list_pop(c_fixed_list_t* list, void* out_data);

uint32_t c_fixed_list_get_count(c_fixed_list_t* list);

uint32_t c_fixed_list_get_capacity(c_fixed_list_t* list);

c_fixed_list_node_t* c_fixed_list_get_first_node(c_fixed_list_t* list);

c_fixed_list_node_t* c_fixed_list_get_next_node(c_fixed_list_t* list, c_fixed_list_node_t* curr_node);

c_bool_t c_fixed_list_get_node_data(c_fixed_list_t* list, c_fixed_list_node_t* node, void* out_data);

END_C_DECLS

#endif
