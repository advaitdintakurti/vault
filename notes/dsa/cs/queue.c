#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Array-based Queue

typedef struct {
    int front, rear, size;
    unsigned capacity;
    int *array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->capacity = capacity;
    queue->front = 0;
    queue->size = 0;
    // Rear starts at last index.
    queue->rear = capacity - 1;
    queue->array = (int*) malloc(queue->capacity * sizeof(int));
    if (!queue->array) {
        free(queue);
        return NULL;
    }
    return queue;
}

int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue %d\n", item);
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
    printf("Enqueued %d\n", item);
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return INT_MIN;
    }
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

int front(Queue* queue) {
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

int rear(Queue* queue) {
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}

// Display all elements in the queue.
void displayQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue: ");
    for (unsigned i = 0, idx = queue->front; i < queue->size; i++) {
        printf("%d ", queue->array[idx]);
        idx = (idx + 1) % queue->capacity;
    }
    printf("\n");
}

// Search for an element in the queue. Returns index or -1 if not found.
int searchQueue(Queue* queue, int item) {
    if (isEmpty(queue))
        return -1;
    for (unsigned i = 0, idx = queue->front; i < queue->size; i++) {
        if (queue->array[idx] == item)
            return idx;
        idx = (idx + 1) % queue->capacity;
    }
    return -1;
}

// Clear the queue (simply resets indices and size)
void clearQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = queue->capacity - 1;
    queue->size = 0;
    printf("Queue cleared.\n");
}

// Free memory allocated for the queue.
void freeQueue(Queue* queue) {
    if (queue) {
        free(queue->array);
        free(queue);
    }
}

// Resize the queue dynamically (only works on array copy, does not preserve circular order)
Queue* resizeQueue(Queue* queue, unsigned newCapacity) {
    if (newCapacity < queue->size) {
        printf("New capacity must be >= current size.\n");
        return queue;
    }
    int *newArray = (int*) malloc(newCapacity * sizeof(int));
    if (!newArray) return queue;
    // Copy elements in order.
    for (unsigned i = 0, idx = queue->front; i < queue->size; i++) {
        newArray[i] = queue->array[idx];
        idx = (idx + 1) % queue->capacity;
    }
    free(queue->array);
    queue->array = newArray;
    queue->capacity = newCapacity;
    queue->front = 0;
    queue->rear = queue->size - 1;
    printf("Queue resized to capacity %u.\n", newCapacity);
    return queue;
}

/************************************
 * 2. LINKED LIST-BASED QUEUE IMPLEMENTATION
 ************************************/

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node *front, *rear;
} LLQueue;

// Create a new linked list based queue.
LLQueue* createLLQueue() {
    LLQueue* q = (LLQueue*) malloc(sizeof(LLQueue));
    if (!q)
        return NULL;
    q->front = q->rear = NULL;
    return q;
}

// Enqueue for linked list based queue.
void llEnqueue(LLQueue *q, int item) {
    Node* temp = (Node*) malloc(sizeof(Node));
    if (!temp) return;
    temp->data = item;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        printf("Enqueued %d in LLQueue\n", item);
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
    printf("Enqueued %d in LLQueue\n", item);
}

// Dequeue for linked list based queue.
int llDequeue(LLQueue *q) {
    if (q->front == NULL) {
        printf("Linked List Queue is empty.\n");
        return INT_MIN;
    }
    Node* temp = q->front;
    int item = temp->data;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return item;
}

// Get front of linked list queue.
int llFront(LLQueue *q) {
    if (q->front == NULL)
        return INT_MIN;
    return q->front->data;
}

// Display linked list queue.
void displayLLQueue(LLQueue *q) {
    if (q->front == NULL) {
        printf("Linked List Queue is empty.\n");
        return;
    }
    printf("LLQueue: ");
    Node* temp = q->front;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Search for an element in the linked list queue.
int searchLLQueue(LLQueue *q, int item) {
    int pos = 0;
    Node* temp = q->front;
    while (temp) {
        if (temp->data == item)
            return pos;
        pos++;
        temp = temp->next;
    }
    return -1;
}

// Clear the linked list queue.
void clearLLQueue(LLQueue *q) {
    while (q->front) {
        Node* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
    printf("LLQueue cleared.\n");
}

// Free memory allocated for the linked list queue.
void freeLLQueue(LLQueue *q) {
    clearLLQueue(q);
    free(q);
}

// Monotonic Queue

// Sliding Window Maximum
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (!numsSize) {
        *returnSize = 0;
        return NULL;
    }
    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    *returnSize = 0;
    Queue* q = createQueue(numsSize);
    for (int i = 0; i < numsSize; i++) {
        while (!isEmpty(q) && q->array[q->front] < i - k + 1)
            dequeue(q);
        while (!isEmpty(q) && nums[q->array[q->rear]] < nums[i]) {
            q->rear = (q->rear - 1 + q->capacity) % q->capacity;
            q->size--;
        }
        enqueue(q, i);
        if (i >= k - 1)
            result[(*returnSize)++] = nums[q->array[q->front]];
    }
    freeQueue(q);
    return result;
}