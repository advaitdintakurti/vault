
![[stack-heap.png]]

There are two types of memory allocation: static and dynamic.
### Static Allocation

Memory is allocated at compile time, and the size and location are determined before the program starts executing. This type of memory is typically allocated on the stack and cannot change size during the program's execution.

- **Fixed size**: Once defined, the memory cannot grow or shrink.
- **Stack-based**: Memory is automatically managed and released when the function scope ends.
```c
int arr[77]; // Static allocation of an array of size 77
```
### Dynamic Allocation

Memory is allocated at runtime, and the size can vary during the program's execution. Dynamic memory allocation occurs on the heap, and the programmer is responsible for managing (allocating and deallocating) the memory manually.

- **Variable size**: The memory size can change during execution.
- **Heap-based**: The memory is allocated from the heap, not automatically managed.
- **Explicit management**: Requires the use of specific functions to allocate and free memory.

### Memory Allocation Functions in C

C provides several functions in the `<stdlib.h>` library to manage dynamic memory allocation:

#### `malloc()`
```c
void* malloc(size_t size);
```

Allocates a block of memory of the specified size and returns a pointer to the beginning of the block. The contents of the allocated memory are not initialized.

```c
int *var = (int*)malloc(sizeof(int));
if (var == NULL) {
    // Handle allocation failure
}
*var = 100;
```

#### `calloc()`
```c
void* calloc(size_t num, size_t size);
```

Allocates memory for an array of elements, initializes all bytes to zero, and returns a pointer to the allocated memory.

```c
int *arr = (int*)calloc(10, sizeof(int));  // Allocates memory for 10 integers and initializes to 0
```

#### `realloc()`
```c
void* realloc(void* ptr, size_t size);
```

Changes the size of a previously allocated memory block. It can expand or shrink the memory, copying the existing contents to the new block if necessary.

```c
int *arr = (int*)realloc(arr, 20 * sizeof(int));  // Resizes the array to hold 20 integers
```

#### `free()`

```c
void free(void* ptr);
```
Deallocates the memory previously allocated by `malloc()`, `calloc()`, or `realloc()`, returning it to the system.

```c
free(var);  // Deallocate memory
```

### Allocating Multi-dimensional Arrays Dynamically

#### Array of Pointers

In this approach, we allocate memory for an array of pointers first, and then for each row individually.
```c
int* arr[m];  // Array of pointers

for (int i = 0; i < m; i++) {
    arr[i] = (int*)malloc(n * sizeof(int));  // Allocate memory for each row
}
```

#### Pointer to Pointer

This approach uses a double pointer to allocate a 2D array dynamically. First, we allocate memory for an array of pointers, then allocate memory for each row.
```c
int** arr = (int**)malloc(m * sizeof(int*));  // Allocate memory for row pointers

for (int i = 0; i < m; i++) {
    arr[i] = (int*)malloc(n * sizeof(int));  // Allocate memory for each row
}
```

#### Single Allocation for Entire 2D Array

In this approach, we allocate memory for the entire 2D array in a single `malloc()` call and access the array using pointer arithmetic.
```c
int* arr = (int*)malloc(m * n * sizeof(int));  // Allocate memory for m * n integers

// Accessing elements
for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        arr[i * n + j] = i + j;  // Access element at row i and column j
    }
}
```


#### Dynamic Allocation of 2D Array

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int m = 3, n = 4;

    // Pointer to a pointer (2D array)
    int** arr = (int**)malloc(m * sizeof(int*));  // Allocate memory for row pointers

    for (int i = 0; i < m; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));   // Allocate memory for each row
    }

    // Initializing the 2D array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            arr[i][j] = i + j;
        }
    }

    // Printing the 2D array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    // Free the allocated memory
    for (int i = 0; i < m; i++) {
        free(arr[i]);  // Free each row
    }
    free(arr);  // Free the array of pointers

    return 0;
}

```

### Memory Allocation Summary

| Function    | Purpose                                                | Usage                       |     |
| ----------- | ------------------------------------------------------ | --------------------------- | --- |
| `malloc()`  | Allocates a block of memory of the specified size.     | Single objects or arrays.   |     |
| `calloc()`  | Allocates memory for an array and initializes to zero. | Arrays or multiple objects. |     |
| `realloc()` | Resizes a previously allocated memory block.           | Resizing arrays.            |     |
| `free()`    | Deallocates previously allocated memory.               | Memory cleanup.             |     |

---
Next: [[Functions]]