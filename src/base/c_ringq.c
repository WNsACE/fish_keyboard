#include "c_ringq.h"

c_ringq_t* c_ringq_init(c_ringq_t* ringq, void** data_list, uint32_t max_size) {
  if (ringq != NULL) {
    memset(ringq, 0x0, sizeof(c_ringq_t));
    ringq->max_size = max_size;
    ringq->data_list = data_list;
    ringq->tag |= C_RINGQ_TAG_EMPTY;
  }
  return ringq;
}

c_bool_t c_ringq_is_full(c_ringq_t* ringq) {
  return ringq->head == ringq->tail && ringq->tag & C_RINGQ_TAG_FULL;
}

c_bool_t c_ringq_is_empty(c_ringq_t* ringq) {
  return ringq->head == ringq->tail && ringq->tag & C_RINGQ_TAG_EMPTY;
}

int32_t c_ringq_push(c_ringq_t* ringq, void* data) {
  if (ringq != NULL && !c_ringq_is_full(ringq)) {
    if (++ringq->tail == ringq->max_size) {
      ringq->tail = 0;
    }
    if (ringq->head == ringq->tail) {
      ringq->tag |= C_RINGQ_TAG_FULL;
      ringq->tag &= ~C_RINGQ_TAG_EMPTY;
    }
    ringq->data_list[ringq->tail] = data;
    return ringq->tail;
  }
  return -1;
}

void* c_ringq_pup(c_ringq_t* ringq) {
  if (ringq != NULL && !c_ringq_is_empty(ringq)) {
    void* data = ringq->data_list[ringq->head];
    if (++ringq->head == ringq->max_size) {
      ringq->head = 0;
    }
    if (ringq->head == ringq->tail) {
      ringq->tag &= ~C_RINGQ_TAG_FULL;
      ringq->tag |= C_RINGQ_TAG_EMPTY;
    }
    return data;
  }
  return NULL;
}

void c_ringq_foreach(c_ringq_t* ringq, c_foreach_cb_t cb, void* ctx) {
  if (ringq != NULL && !c_ringq_is_empty(ringq) && cb != NULL) {
    uint32_t head = ringq->head;
    do {
      cb(ringq->data_list[head], ctx);
      if (++head == ringq->max_size) {
        head = 0;
      }
    } while (ringq->head == ringq->tail);
  }
}
