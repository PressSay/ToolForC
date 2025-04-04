#ifndef QUEUE_C
#define QUEUE_C
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _q_data {
  void *data;
  struct _q_data *next;
} _q_data;

typedef struct queue_t {
  size_t size;
  size_t allocation_size;
  _q_data *head;
  _q_data *tail;
} queue_t;


/**
 * @param alloc_size size of elements inserted
 * @return queue on success, NULL on error
 */
queue_t *create_queue(size_t alloc_size);

/**
 * @param q The queue
 * @param data Data to be inserted
 * @return queue on success, NULL on error
 */
queue_t *enqueue(queue_t *q, void *data);

/**
 * @param q The queue
 * @param deletedElem The element deleted
 * @return queue on success, NULL on error
 */
queue_t *dequeue(queue_t *q, void *to_ret);

/**
 * @param q The queue
 * @return size_t Size of queue
 */
size_t size_queue(queue_t *q);

/**
 * @brief Delete all the elements of the queue and that queue
 * @param q The queue
 */
void free_queue(queue_t *q);

/**
 * @brief clone new queue for browsing
 * @return 1 success, 0 false
 */
int copy_queue(queue_t *dirt, const queue_t *source);

/**
 * @brieft Reverse the queue
 * @param The queue
 * @return q, NULL on error
 */
queue_t *reverse(queue_t *q);


#ifdef __cplusplus
}
#endif

#endif
