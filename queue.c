#include "queue.h"

queue_t *create_queue(size_t alloc_size) {
  queue_t *result = malloc(sizeof(queue_t));
  result->allocation_size = alloc_size;
  result->size = 0;
  return result;
}

queue_t *enqueue(queue_t *q, void *data) {
  if (q == NULL)
    return NULL;

  _q_data *to_insert = malloc(sizeof(_q_data));
  if (to_insert == NULL)
    return NULL;

  to_insert->data = malloc(q->allocation_size);
  if (to_insert->data == NULL)
    return NULL;

  to_insert->next = NULL;
  memcpy(to_insert->data, data, q->allocation_size);

  if (q->size == 0) {
    q->head = q->tail = to_insert;
  } else {
    q->tail->next = to_insert;
    q->tail = q->tail->next;
  }

  q->size++;

  return q;
}

queue_t *dequeue(queue_t *q, void *to_ret) {
  if (q == NULL || q->size == 0)
    return NULL;

  _q_data *to_del = q->head;

  memcpy(to_ret, to_del->data, q->allocation_size);

  if (q->size == 1) {
    q->head = q->tail = NULL;
  } else {
    q->head = q->head->next;
  }

  free(to_del->data);
  free(to_del);

  q->size--;
  return q;
}

size_t size_queue(queue_t *q) { return q->size; }

int copy_queue(queue_t *dirt, const queue_t *source) {
  if (dirt == NULL || dirt->size != 0 ||
      dirt->allocation_size != source->allocation_size)
    return 0;
  _q_data *data_trv = source->head;
  while (data_trv != NULL) {
    dirt = enqueue(dirt, data_trv->data);
    if (dirt == NULL)
      return 0;
    data_trv = data_trv->next;
  }
  return 1;
}

void free_queue(queue_t *q) {
  if (q == NULL)
    return;
  void *tmp = malloc(q->allocation_size);
  while (q->size != 0) {
    dequeue(q, tmp);
  }
  free(tmp);
  free(q);
}

queue_t *reverse(queue_t *q) {
  if (q == NULL)
    return NULL;
  if (size_queue(q) == 0)
    exit(1);
  else {
    _q_data temp;
    dequeue(q, &temp);
    reverse(q);
    enqueue(q, &temp);
    return q;
  }
}
