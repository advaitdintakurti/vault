A **heap** is a specialized **binary tree** that satisfies the **heap property**. It is commonly used in priority queues and sorting algorithms like Heap Sort. A heap is a **complete binary tree**, meaning all levels are completely filled except possibly the last level, which is filled from left to right.

There are two types of heaps:

1. **Max Heap**: The key at each parent node is **greater than or equal to** the keys of its children. The largest element is always at the root.
2. **Min Heap**: The key at each parent node is **less than or equal to** the keys of its children. The smallest element is always at the root.

Heap operations typically involve **insertion**, **deletion**, and **heapification**, which maintain the heap structure.

### **Heap Representation in an Array**

Since a heap is a complete binary tree, it is efficiently stored as an **array** where:

- The **root** is at index **0**.
- The **left child** of node at index `i` is at index `2*i + 1`.
- The **right child** of node at index `i` is at index `2*i + 2`.
- The **parent** of node at index `i` is at index `(i - 1) / 2`.

This structure allows easy access to children and parents without using pointers.

### **Example of a Max Heap**

```
         16
       /    \
      14     10
     /  \   /  \
    8    7 9    3
   / \
  2   4
```

**Array Representation**:  
`[16, 14, 10, 8, 7, 9, 3, 2, 4]`

### **Heap Operations**

1. **Heapify**: Maintains the heap property by moving a node down the tree until the max heap (or min heap) condition is restored.
2. **Build Heap**: Converts an arbitrary array into a heap using `heapify` in O(n)O(n) time.
3. **Extract Max/Min**: Removes the root and reorders the heap using `heapify`, taking O(log⁡n)O(\log n).
4. **Insert**: Adds an element at the end and moves it up the tree if necessary, taking O(log⁡n)O(\log n).


### Parent, Left and Right
```c
// Input: A: an array representing a heap, i: an array index
// Output: The index in A of the parent of i
// Running Time: O(1)
int Parent(int i) {
    if (i == 1) return -1; // Assuming the heap starts at index 1
    return i / 2;
}

// Input: A: an array representing a heap, i: an array index
// Output: The index in A of the left child of i
// Running Time: O(1)
int Left(int i) {
    return 2 * i;
}

// Input: A: an array representing a heap, i: an array index
// Output: The index in A of the right child of i
// Running Time: O(1)
int Right(int i) {
    return 2 * i + 1;
}
```

### Max Heapify
```c
// Input: A: an array where the left and right children of i root heaps (but i may not), i: an array index
// Output: A modified so that i roots a heap
// Running Time: O(log n) where n = heap-size[A] − i
void MaxHeapify(int A[], int size, int i) {
    int l = Left(i);
    int r = Right(i);
    int largest = i;

    if (l <= size && A[l] > A[i])
        largest = l;

    if (r <= size && A[r] > A[largest])
        largest = r;

    if (largest != i) {
        // Swap A[i] and A[largest]
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        // Recursively heapify the affected subtree
        MaxHeapify(A, heap_size, largest);
    }
}
```

### Build Max Heap
```c
// Input: A: an (unsorted) array
// Output: A modified to represent a heap.
// Running Time: O(n) where n = length[A]
void BuildMaxHeap(int A[], int length) {
    int size = length;
    // non-leaf nodes
    for (int i = length / 2; i >= 1; i--) {
        MaxHeapify(A, size, i);
    }
}
```

### Heap Increase Key
```c
// Input: A: heap array, i: array index, key: a new key greater than A[i]
// Output: A still representing a heap where the key of A[i] was increased to key
// Running Time: O(log n) where n = heap-size[A]
void HeapIncreaseKey(int A[], int i, int key) {
    if (key < A[i]) {
        printf("Error: New key must be larger than current key.\n");
        return;
    }
    A[i] = key;
    while (i > 1 && A[Parent(i)] < A[i]) {
        // Swap A[i] and A[Parent(i)]
        int temp = A[i];
        A[i] = A[Parent(i)];
        A[Parent(i)] = temp;

        i = Parent(i);
    }
}
```

### Heap Sort
```c
// Input: A: an (unsorted) array
// Output: A modified to be sorted from smallest to largest
// Running Time: O(n log n) where n = length[A]
// sorts an array by building a max-heap and then repeatedly extracting the maximum element.
void HeapSort(int A[], int length) {
    BuildMaxHeap(A, length);
    int heap_size = length;
    for (int i = length; i >= 2; i--) {
        // Swap A[1] and A[i]
        int temp = A[1];
        A[1] = A[i];
        A[i] = temp;

        heap_size--;
        MaxHeapify(A, heap_size, 1);
    }
}
```

### Heap Extract Max
```c
// Input: A: an array representing a heap
// Output: The maximum element of A and A as a heap with this element removed
// Running Time: O(log n) where n = heap-size[A]
// extracts the maximum element from the heap and ensures the heap property is maintained
int HeapExtractMax(int* A, int *heap_size) {
    int max = A[1];
    A[1] = A[*heap_size];
    (*heap_size)--;
    MaxHeapify(A, *heap_size, 1);
    return max;
}
```

### Max Heap Insert
```c
void MaxHeapInsert(int A[], int *heap_size, int key) {
    (*heap_size)++;
    A[*heap_size] = INT_MIN;
    HeapIncreaseKey(A, *heap_size, key);
}
```