
#### Header Files
Header Files contain function prototypes, structs, macros and type definitions.
They are used to expose functions between `.c` files.


`list.h`
```c
#ifndef LIST_H
#define LIST_H

typedef struct Node Node;

typedef Node* ListNode;

struct Node {
    int val;
    struct Node* next;
};

// function prototypes for list operations
ListNode append(int val, ListNode l);
int size(ListNode l);

#endif // LIST_H
```

> NOTE: we use `#ifndef`, `#define`, and `#endif` to prevent multiple inclusions of the same file (header guards).

#### Other File
This is where the functions are implemented.

`list.c`
```c
#include "list.h"
#include <stdlib.h> // for malloc

// function to calculate the size of a linked list.
int size(ListNode l) {
    return l == NULL ? 0 : 1 + size(l->next);
}

// function to append a value to the end of a linked list.
ListNode append(int val, ListNode l) {   
    if (l == NULL) {
        Node* newNode = (Node*) malloc(sizeof(Node));
        newNode->val = val;
        newNode->next = NULL;
        return newNode;
    } else {
        l->next = append(val, l->next);
    }
    return l;
}
```

#### `main.c`
```c
#include "list.h"
#include "stdio.h"

// you can use the functions defined in list.c now
int main() {
    ListNode head = NULL;
    
    head = append(1, head);
    head = append(2, head);
    head = append(3, head);

    printf("size of list: %d\n", size(head));

    return 0;
}

```

### Compiling Multifile Codebases

In C, to compile a program spread across multiple `.c` files, you need to pass each `.c` file to `gcc`:
```bash
gcc main.c list.c -o main
```

This command compiles both `main.c` and `list.c`, linking them into a single executable named `main`.

---
Next: [[Debugging]]

