A pointer is a variable that stores the memory address of another variable.

A pointer is declared by specifying the data type it will point to, followed by an asterisk `*` and the pointer name.
```c
int *ptr;
int val = 42;
ptr = &val;
```
Pointers are typically initialized with the address of a variable using the address-of operator `&`

#### Dereferencing Pointers
- Dereferencing a pointer means accessing the value stored at the memory address the pointer is holding.
- The dereference operator `*` is used to get the value at the pointer's address.
```c
int var = 42;
int *p = &var;
printf("%d", *p); // Output: 42
```

#### Pointer Arithmetic
- Pointers can be incremented or decremented to traverse arrays or memory blocks.
- When you increment a pointer, it moves to the next memory location based on the size of the data type it points to.
```c
int arr[] = {6, 9, 2024};
int *p = arr;    // Points to the first element of the array
p++;             // Now p points to the second element
printf("%d", *p); // Output: 9
```
#### Pointers and Arrays
- The name of an array in C is essentially a pointer to its first element.
- This allows pointers to be used to traverse arrays efficiently.

```c
int arr[] = {1, 2, 3, 4};
int *p = arr;
for(int i = 0; i < 4; i++) {
    printf("%d ", *(p + i)); // Output: 1 2 3 4
}
```

**Three terms:**  
`arr`, `&arr`, `&arr[0]` all print the same thing, but have different meanings:
- `arr` refers to the array itself, it points to `[0]` index
- `&arr` points to the **entire** array
- `&arr[0]` points to the first element

> **Note:** `&arr + 1` points to the element immediately after the end of the array, not to the second element of the array (`&arr` points to the entire array)

#### Pointer to Array
```c
int(*b)[10];

int arr[10] = {2,3,4,6,3,6,2,4,88,1};
b = &arr;
```

Elements of `arr` can be accessed via `b` using `(*b)[i]` or `*(*b + i)`
> `(*b)[i]` ==  `&arr[i]` (as `(*b)` refers to `arr`)
> `*(*b + i)` == `*(arr + i)` == `&arr[i]`

#### Array of Pointers
```c
int *b[10]; // array of type int *
int arr[10] = {2,3,4,6,3,6,2,4,88,1};

for(int i = 0; i < 10; i++) {
    b[i] = &arr[i];
}

for(int i = 0; i < 10; i++) {
    printf("%d", *b[i]);
}
```

#### Pointer to Pointer
```c
int var = 88;
int *p = &var;
int **q = &p;   // q is a pointer to p
printf("%d", **q); // Output: 88
```
`q` points to the memory address where `p` is stored.

#### Pointers and 2D arrays
To get address of (i,j)<sup>th</sup> element
```c
printf("%p", *(arr + i) + j)
```
#### Advantages of Pointers
- **Efficient Memory Use**: Pointers allow for dynamic memory allocation, enabling efficient use of memory.
- **Direct Memory Access**: Pointers can access and manipulate memory locations directly, making certain operations faster.
- **Functionality**: Pointers enable the implementation of complex data structures (e.g., linked lists, trees) and functions that require dynamic memory.

---
Next: [[Strings]]