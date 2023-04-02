#include "c_list.h"

static int c_list_node_compare_default(void* a, void* b) {
  return a == b ? 0 : 1;
}

c_list_t* c_list_init(c_list_t* list, c_list_node_create_t list_node_create, c_list_node_destroy_t list_node_destroy, c_list_node_compare_t list_node_compare) {
  if (list != NULL) {
    memset(list, 0x0, sizeof(c_list_t));
    list->list_node_create = list_node_create;
    list->list_node_destroy = list_node_destroy;
    list->list_node_compare = list_node_compare != NULL ? list_node_compare : c_list_node_compare_default;
  }
  return list;
}

c_bool_t c_list_push_front(c_list_t* list, void* data) {
  if (list != NULL) {
    c_list_node_t* head = &list->head;
    c_list_node_t* node = list->list_node_create(data);
    if (node != NULL) {
      list->size++;
      node->next = head;
      list->head.next = node;
      return TRUE;
    }
  }
  return FALSE;
}

c_bool_t c_list_push_back(c_list_t* list, void* data) {
  if (list != NULL) {
    c_list_node_t* node = list->list_node_create(data);
    if (node != NULL) {
      list->size++;
      node->next = NULL;
      list->tail->next = node;
      list->tail = node;
      return TRUE;
    }
  }
  return FALSE;
}

void c_list_foreach(c_list_t* list, c_foreach_cb_t cb, void* ctx) {
  if (list != NULL) {
    c_list_node_t* node = list->head.next;
    while (node != NULL) {
      c_list_node_t* next = node->next;
      cb((void*)node, ctx);
      node = next;
    }
  }
}

void c_list_remove(c_list_t* list, void* data) {
  if (list != NULL) {
    c_list_node_t* prev = &list->head;
    c_list_node_t* node = list->head.next;
    while (node != NULL) {
      c_list_node_t* next = node->next;
      if (list->list_node_compare(node->data, data) == 0) {
        prev->next = next;
        list->list_node_destroy(node);
        list->size--;
        node = next;
        continue;
      }
      prev = node;
      node = next;
    }
  }
}

void c_list_deinit(c_list_t* list) {
  if (list != NULL) {
    c_list_node_t* node = list->head.next;
    while (node != NULL) {
      c_list_node_t* next = node->next;
      list->list_node_destroy(node);
      node = next;
    }
  }
}

