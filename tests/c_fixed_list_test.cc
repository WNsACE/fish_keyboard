#include "gtest/gtest.h"
#include "base/c_fixed_list.h"

typedef struct _point_t {
  uint32_t x;
  uint32_t y;
} point_t;

#define FIXED_LIST_MAX_SIZE 5

C_FIXED_LIST_DEFINE(point_t, FIXED_LIST_MAX_SIZE)

static int fixed_list_on_compare(void* a, void* b) {
  point_t* point_a = (point_t*)a;
  point_t* point_b = (point_t*)b;
  if (point_a->y != point_b->y) {
    return point_a->y - point_b->y;
  }
  return point_a->x - point_a->x;
}

TEST(c_fixed_list, init) {
  C_FIXED_LIST_TYPE_T(point_t) list;
  c_fixed_list_t* p_list = c_fixed_list_init((c_fixed_list_t*)&list, C_FIXED_LIST_GET_TYPE_SIZE(point_t), FIXED_LIST_MAX_SIZE, sizeof(point_t), fixed_list_on_compare);
  uint8_t* p_fixed_mem_data = (uint8_t*)(list.fixed_mem_data);
  c_bool_t* p_fixed_free_mem_data = list.fixed_free_mem_data;
  c_fixed_list_node_t* p_fixed_mem_node = list.fixed_mem_node;


  ASSERT_EQ(p_list->p_fixed_mem_data, p_fixed_mem_data);
  ASSERT_EQ(p_list->p_fixed_mem_node, p_fixed_mem_node);
  ASSERT_EQ(p_list->p_fixed_free_mem_data, p_fixed_free_mem_data);

  c_fixed_list_deinit(p_list);
}

TEST(c_fixed_list, push_and_pop) {
  C_FIXED_LIST_TYPE_T(point_t) list;
  c_fixed_list_t* p_list = c_fixed_list_init((c_fixed_list_t*)&list, C_FIXED_LIST_GET_TYPE_SIZE(point_t), FIXED_LIST_MAX_SIZE, sizeof(point_t), fixed_list_on_compare);

  point_t p0 = {0, 0};
  point_t p1 = {10, 10};
  point_t p2 = {20, 20};
  point_t p3 = {30, 30};
  point_t p4 = {40, 40};
  point_t p5 = {50, 50};
  point_t p6 = {60, 60};

  ASSERT_EQ(c_fixed_list_get_capacity(p_list), FIXED_LIST_MAX_SIZE);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p1) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 1);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p2) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 2);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p3) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 3);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p4) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 4);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p5) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p6) == FALSE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), FIXED_LIST_MAX_SIZE);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p1.x && p0.y == p1.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 4);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p6) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p2.x && p0.y == p2.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 4);
  
  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p3.x && p0.y == p3.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 3);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p4.x && p0.y == p4.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 2);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p5.x && p0.y == p5.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 1);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p6.x && p0.y == p6.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 0);

  c_fixed_list_deinit(p_list);
}

TEST(c_fixed_list, sorted_insert) {
  C_FIXED_LIST_TYPE_T(point_t) list;
  c_fixed_list_t* p_list = c_fixed_list_init((c_fixed_list_t*)&list, C_FIXED_LIST_GET_TYPE_SIZE(point_t), FIXED_LIST_MAX_SIZE, sizeof(point_t), fixed_list_on_compare);

  point_t p0 = {0, 0};
  point_t p1 = {10, 10};
  point_t p2 = {20, 20};
  point_t p3 = {30, 30};
  point_t p4 = {40, 40};
  point_t p5 = {50, 50};
  point_t p6 = {60, 60};

  ASSERT_EQ(c_fixed_list_get_capacity(p_list), FIXED_LIST_MAX_SIZE);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p6) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 1);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p2) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 2);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p3) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 3);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p5) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 4);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p4) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p1) == FALSE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), FIXED_LIST_MAX_SIZE);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p2.x && p0.y == p2.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 4);
  
  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p3.x && p0.y == p3.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 3);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p4.x && p0.y == p4.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 2);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p5.x && p0.y == p5.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 1);

  ASSERT_EQ(c_fixed_list_pop(p_list, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p6.x && p0.y == p6.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 0);

  c_fixed_list_deinit(p_list);
}

TEST(c_fixed_list, get_next_node) {
  C_FIXED_LIST_TYPE_T(point_t) list;
  c_fixed_list_t* p_list = c_fixed_list_init((c_fixed_list_t*)&list, C_FIXED_LIST_GET_TYPE_SIZE(point_t), FIXED_LIST_MAX_SIZE, sizeof(point_t), fixed_list_on_compare);

  point_t p0 = {0, 0};
  point_t p1 = {10, 10};
  point_t p2 = {20, 20};
  point_t p3 = {30, 30};
  point_t p4 = {40, 40};
  point_t p5 = {50, 50};
  point_t p6 = {60, 60};

  ASSERT_EQ(c_fixed_list_get_capacity(p_list), FIXED_LIST_MAX_SIZE);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p2) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 1);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p6) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 2);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p4) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 3);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p5) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 4);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p3) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);

  ASSERT_EQ(c_fixed_list_sorted_insert(p_list, &p1) == FALSE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), FIXED_LIST_MAX_SIZE);

  c_fixed_list_node_t* iter_node = c_fixed_list_get_first_node(p_list);

  ASSERT_EQ(iter_node != NULL, true);
  ASSERT_EQ(c_fixed_list_get_node_data(p_list, iter_node, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p2.x && p0.y == p2.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);

  iter_node = c_fixed_list_get_next_node(p_list, iter_node);
  ASSERT_EQ(iter_node != NULL, true);
  ASSERT_EQ(c_fixed_list_get_node_data(p_list, iter_node, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p3.x && p0.y == p3.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);
  
  iter_node = c_fixed_list_get_next_node(p_list, iter_node);
  ASSERT_EQ(iter_node != NULL, true);
  ASSERT_EQ(c_fixed_list_get_node_data(p_list, iter_node, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p4.x && p0.y == p4.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);
  
  iter_node = c_fixed_list_get_next_node(p_list, iter_node);
  ASSERT_EQ(iter_node != NULL, true);
  ASSERT_EQ(c_fixed_list_get_node_data(p_list, iter_node, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p5.x && p0.y == p5.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);
  
  iter_node = c_fixed_list_get_next_node(p_list, iter_node);
  ASSERT_EQ(iter_node != NULL, true);
  ASSERT_EQ(c_fixed_list_get_node_data(p_list, iter_node, &p0) == TRUE, true);
  ASSERT_EQ(p0.x == p6.x && p0.y == p6.y , true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);

  c_fixed_list_deinit(p_list);
}

static void fixed_list_on_foreach(void* data, void* ctx) {
  point_t* p = (point_t*)data;
  point_t* p3 = (point_t*)ctx;
  ASSERT_NE(p->x, p3->x);
  ASSERT_NE(p->y, p3->y);
}

TEST(c_fixed_list, remove) {
  C_FIXED_LIST_TYPE_T(point_t) list;
  c_fixed_list_t* p_list = c_fixed_list_init((c_fixed_list_t*)&list, C_FIXED_LIST_GET_TYPE_SIZE(point_t), FIXED_LIST_MAX_SIZE, sizeof(point_t), fixed_list_on_compare);

  point_t p0 = {0, 0};
  point_t p1 = {10, 10};
  point_t p2 = {20, 20};
  point_t p3 = {30, 30};
  point_t p4 = {40, 40};
  point_t p5 = {50, 50};

  ASSERT_EQ(c_fixed_list_get_capacity(p_list), FIXED_LIST_MAX_SIZE);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p1) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 1);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p2) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 2);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p3) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 3);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p4) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 4);

  ASSERT_EQ(c_fixed_list_push_back(p_list, &p5) == TRUE, true);
  ASSERT_EQ(c_fixed_list_get_count(p_list), 5);

  ASSERT_EQ(c_fixed_list_remove(p_list, &p3) == TRUE, true);

  c_fixed_list_foreach(p_list, fixed_list_on_foreach, &p3);

  c_fixed_list_deinit(p_list);
}
