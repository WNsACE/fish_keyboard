#include "c_fixed_list.h"

static void c_fixed_list_node_deinit(c_fixed_list_node_t* node) {
  node->curr = -1;
  node->next = NULL;
}

c_fixed_list_t* c_fixed_list_init(c_fixed_list_t* list, uint32_t size, uint32_t fixed_size, uint32_t type_size, c_fixed_list_compare_t compare) {
  int32_t i = 0;
  if (list != NULL && fixed_size > 0 && type_size > 0 && size > sizeof(c_fixed_list_t)) {
    memset(list, 0x0, size);

    list->size = size;
    list->type_size = type_size;
    list->capacity = fixed_size;

    list->compare = compare;

    list->p_fixed_mem_data = (uint8_t*)(((uint8_t*)list) + sizeof(c_fixed_list_t));
    list->p_fixed_free_mem_data = (c_bool_t*)(((uint8_t*)list->p_fixed_mem_data) + (fixed_size * type_size));
    list->p_fixed_mem_node = (c_fixed_list_node_t*)(((uint8_t*)list->p_fixed_free_mem_data) + (fixed_size * sizeof(c_bool_t)));

    for (i = 0; i < list->capacity; i++) {
      list->p_fixed_free_mem_data[i] = TRUE;
      c_fixed_list_node_deinit(&list->p_fixed_mem_node[i]);
    }
    return list;
  }
  return NULL;
}

void c_fixed_list_deinit(c_fixed_list_t* list) {
  if (list != NULL) {
    memset(list, 0x0, list->size);
  }
}

void c_fixed_list_remove(c_fixed_list_t* list, void* data) {
  if (list != NULL) {
    c_fixed_list_node_t* prev = NULL;
    c_fixed_list_node_t* node = list->head;
    while (node != NULL) {
      uint8_t* node_data = (uint8_t*)(list->p_fixed_mem_data + node->curr * list->type_size);
      if (memcmp(node_data, data, list->type_size) == 0) {
        if (prev == NULL) {
          list->head = list->head->next;
        } else {
          prev->next = node->next;
        }
        c_fixed_list_node_deinit(node);
        list->cursor--;
        break;
      }
      prev = node;
      node = node->next;
    }
  }
  return;
}

void c_fixed_list_foreach(c_fixed_list_t* list, c_foreach_cb_t cb) {
  if (list != NULL && cb != NULL) {
    c_fixed_list_node_t* node = list->head;
    while (node != NULL) {
      uint8_t* node_data = (uint8_t*)(list->p_fixed_mem_data + node->curr * list->type_size);
      cb(node_data);
      node = node->next;
    }
  }
}

static int32_t c_fixed_list_get_free_pos(c_fixed_list_t* list) {
  int32_t i = 0;
  for (i = 0; i < list->capacity; i++) {
    if (list->p_fixed_free_mem_data[i]) {
      return i;
    }
  }
  return -1;
}

static c_fixed_list_node_t* c_fixed_list_get_free_node(c_fixed_list_t* list) {
  int32_t i = 0;
  for (i = 0; i < list->capacity; i++) {
    if (list->p_fixed_mem_node[i].curr == -1 && list->p_fixed_mem_node[i].next == NULL) {
      return &(list->p_fixed_mem_node[i]);
    }
  }
  return NULL;
}

static c_fixed_list_node_t* c_fixed_list_set_free_node_data(c_fixed_list_t* list, void* data) {
  int32_t free_pos = c_fixed_list_get_free_pos(list);
  c_fixed_list_node_t* node = c_fixed_list_get_free_node(list);
  if (free_pos >= 0 && node != NULL) {
    list->p_fixed_free_mem_data[free_pos] = FALSE;
    memcpy((uint8_t*)(list->p_fixed_mem_data + free_pos * list->type_size), data, list->type_size);
    node->curr = free_pos;
    node->next = NULL;
    return node;
  }
  return NULL;
}

c_bool_t c_fixed_list_push_back(c_fixed_list_t* list, void* data) {
  if (list != NULL && data != NULL && list->cursor < list->capacity) {
    c_fixed_list_node_t* tail = list->head;
    c_fixed_list_node_t* node = c_fixed_list_set_free_node_data(list, data);
    if (node != NULL) {
      if (tail == NULL) {
        list->head = node;
      } else {
        while (tail->next != NULL) {
          tail = tail->next;
        }
        tail->next = node;
      }
      list->cursor++;
      return TRUE;
    }
  }
  return FALSE;
}

c_bool_t c_fixed_list_sorted_insert(c_fixed_list_t* list, void* data) {
  if (list != NULL && data != NULL && list->cursor < list->capacity) {
    c_fixed_list_node_t* prev_node = NULL;
    c_fixed_list_node_t* curr_node = list->head;
    c_fixed_list_node_t* node = c_fixed_list_set_free_node_data(list, data);
    if (node != NULL) {
      if (curr_node == NULL) {
        list->head = node;
      } else {
        while (curr_node != NULL) {
          uint8_t* node_data = (uint8_t*)(list->p_fixed_mem_data + curr_node->curr * list->type_size);
          if (list->compare(node_data, data) > 0) {
            break;
          }
          prev_node = curr_node;
          curr_node = curr_node->next;
        }
        if (prev_node == NULL) {
          node->next = list->head;
          list->head = node;
        } else {
          node->next = prev_node->next;
          prev_node->next = node;
        }
      }
      list->cursor++;
      return TRUE;
    }
  }
  return FALSE;
}

c_bool_t c_fixed_list_pop(c_fixed_list_t* list, void* out_data) {
  if (list != NULL && out_data != NULL) {
    c_fixed_list_node_t* next = list->head->next;
    uint8_t* data = (uint8_t*)(list->p_fixed_mem_data + list->head->curr * list->type_size);

    memcpy(out_data, data, list->type_size);
    list->p_fixed_free_mem_data[list->head->curr] = TRUE;

    c_fixed_list_node_deinit(list->head);

    list->head = next;
    list->cursor--;
    return TRUE;
  }
  return FALSE;
}

uint32_t c_fixed_list_get_capacity(c_fixed_list_t* list) {
  if (list != NULL) {
    return list->capacity;
  }
  return 0;
}

uint32_t c_fixed_list_get_count(c_fixed_list_t* list) {
  if (list != NULL) {
    return list->cursor;
  }
  return 0;
}

c_fixed_list_node_t* c_fixed_list_get_first_node(c_fixed_list_t* list) {
  if (list != NULL) {
    return list->head;
  }
  return NULL;
}

c_fixed_list_node_t* c_fixed_list_get_next_node(c_fixed_list_t* list, c_fixed_list_node_t* curr_node) {
  if (list != NULL && curr_node != NULL) {
    return curr_node->next;
  }
  return NULL;
}

c_bool_t c_fixed_list_get_node_data(c_fixed_list_t* list, c_fixed_list_node_t* node, void* out_data) {
  if (list != NULL && node != NULL && out_data != NULL) {
    uint8_t* data = (uint8_t*)(list->p_fixed_mem_data + node->curr * list->type_size);
    memcpy(out_data, data, list->type_size);
    return TRUE;
  }
  return FALSE;
}
