
A **queue** is a linear data structure that operates in a **First In, First Out (FIFO)** manner, where the first element added is the first to be removed.

#### Operations

1. **Enqueue**: Adds an element to the rear of the queue.
2. **Dequeue**: Removes and returns the element from the front of the queue.
3. **Front/Peek**: Returns the element at the front without removing it.
4. **isEmpty**: Checks if the queue is empty.
5. **isFull** (for a static array implementation): Checks if the queue is full.

#### **Array Implementation**

Simple but suffers from **wastage of space** unless implemented as a circular queue.

```c
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

// Initialize queue
void init(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is full
int isFull(Queue* q) {
    return q->rear == MAX - 1;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == -1 || q->front > q->rear;
}

// Enqueue operation
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (q->front == -1) q->front = 0; // Initialize front
    q->arr[++(q->rear)] = value;
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1; // Indicating error
    }
    int value = q->arr[q->front++];
    if (q->front > q->rear) // Reset queue if empty
        q->front = q->rear = -1;
    return value;
}

// Peek operation
int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1; // Indicating error
    }
    return q->arr[q->front];
}

// Example usage
int main() {
    Queue q;
    init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    printf("Front element: %d\n", peek(&q)); // 10
    printf("Dequeued: %d\n", dequeue(&q));   // 10
    printf("Dequeued: %d\n", dequeue(&q));   // 20
    printf("Is Empty: %d\n", isEmpty(&q));   // 1 (true)

    return 0;
}
```

#### **Linked List Implementation**

Dynamic size. Requires more memory for pointers.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Initialize queue
void init(Queue* q) {
    q->front = q->rear = NULL;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue operation
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Heap Overflow\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (!q->front) {
        q->front = newNode;
    }
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1; // Indicating error
    }
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }
    free(temp);
    return value;
}

// Peek operation
int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1; // Indicating error
    }
    return q->front->data;
}

// Example usage
int main() {
    Queue q;
    init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    printf("Front element: %d\n", peek(&q)); // 10
    printf("Dequeued: %d\n", dequeue(&q));   // 10
    printf("Dequeued: %d\n", dequeue(&q));   // 20
    printf("Is Empty: %d\n", isEmpty(&q));   // 1 (true)

    return 0;
}
```

#### **Circular Queue Implementation**

Efficient array-based implementation that reuses space.

```c
#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct {
    int arr[MAX];
    int front, rear, size;
} CircularQueue;

// Initialize queue
void init(CircularQueue* q) {
    q->front = q->rear = -1;
    q->size = 0;
}

// Check if queue is full
int isFull(CircularQueue* q) {
    return q->size == MAX;
}

// Check if queue is empty
int isEmpty(CircularQueue* q) {
    return q->size == 0;
}

// Enqueue operation
void enqueue(CircularQueue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = value;
    if (q->front == -1) q->front = 0;
    q->size++;
}

// Dequeue operation
int dequeue(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1; // Indicating error
    }
    int value = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return value;
}

// Peek operation
int peek(CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1; // Indicating error
    }
    return q->arr[q->front];
}

// Example usage
int main() {
    CircularQueue q;
    init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    printf("Front element: %d\n", peek(&q)); // 10
    printf("Dequeued: %d\n", dequeue(&q));   // 10
    printf("Dequeued: %d\n", dequeue(&q));   // 20
    printf("Is Empty: %d\n", isEmpty(&q));   // 1 (true)

    return 0;
}
```