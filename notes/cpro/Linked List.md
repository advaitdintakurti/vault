A **linked list** in C is a dynamic data structure where elements, called **nodes**, are stored in non-contiguous memory locations. Each node contains two parts:

1. **Data**: Stores the actual value.
2. **Pointer**: Stores the address of the next node in the list.

```c
struct Node {
  int data;
  struct Node* next;
};
```

In a **singly linked list**, each node points to the next node in the sequence. The last node's pointer is set to `NULL` as it is the end.

```c
int main() {
  struct Node* l = NULL;
  struct Node C = { 1, NULL };
  struct Node B = { 17, &C };
  struct Node A = { 55, &B };
  l = &A;
  return 0;
}
```

### Print all members of linked list
```c
void printlist(struct Node* l) {
  while(l != NULL) {
    printf("%d ", l->data);
    l = l->next;
  }
  printf("\n");
}
```

### Find size of linked list
```c
int sizelist(struct Node *l) {
  int sum = 0;
  while(l != NULL) {
    sum += sizeof(l->data);
    l = l->next;
  }
  return sum;
}
```

### Create Node
```c
struct Node *createNode(int val) {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->data = val;
    new->next = NULL;
    return new;
}
```
### Add to linked list
```c
struct Node* addNode(struct Node* head, int val){
    if(!head) {
        head = createNode(val);
        return head;
    }
    struct Node* l = head;
    while(l->next) {
        l = l->next;
    }
    l->next = createNode(val);
    return head;
}
```

### Insert in Linked List
By position:
```c
struct Node* insert(struct Node* head, int data, int pos) {
    if (pos == 0) {
        struct Node* new = createNode(data);
        new->next = head;
        return new;
    }
    
    struct Node* current = head;
    for(int i = 0; i < pos-1 && current; i++) {
        current = current->next;
    }
    
    if (!current) return head;
    
    struct Node* new = createNode(data);
    new->next = current->next;
    current->next = new;
    
    return head;
}
```

By value:
> wait does this work?
```c
struct Node* insert(struct Node* head, int a, int b) {
    struct Node* temp = head;
    while (temp && temp->data != a) temp = temp->next;
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->data = b;
    new->next = temp->next;
    temp->next = new;
    return head;
}
```

### Reverse Linked List
```c
struct Node *reverse(struct Node *head) {
    struct Node *prev = NULL, *curr = head, *next;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

### Why/When to use linked lists
- **Dynamic Memory Allocation**: Unlike arrays, linked lists can grow or shrink at runtime without needing to know the size in advance.
- **Efficient Insertions/Deletions**: Inserting or deleting nodes at the beginning, middle, or end is efficient, especially compared to arrays where shifting elements is needed.

### Disadvantages
- **No Direct Access to random elements**: Elements cannot be accessed directly using indices like arrays; you must traverse the list from the head.
- **Memory Used**: Each node requires extra memory for the pointer(s) in addition to the data.
- **Not contiguous**: Members of a linked list may not be stored contiguously in memory.

### Common Operations Time Complexity
- **Access**: O(n) - Must traverse the list
- **Search**: O(n) - Must traverse the list
- **Insertion**: O(1) - When inserting at a known position
- **Deletion**: O(1) - When deleting at a known position

### Delete Node
```c
struct Node* deleteNode(struct Node* head, int val) {
    if (!head) return NULL;
    
    if (head->data == val) {
        struct Node* temp = head->next;
        free(head);
        return temp;
    }
    
    struct Node* current = head;
    while (current->next && current->next->data != val) {
        current = current->next;
    }
    
    if (current->next) {
        struct Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    
    return head;
}
```

### Check if List Contains Cycle
```c
bool hasCycle(struct Node* head) {
    struct Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

### Variations
- **Doubly Linked List**: Each node has pointers to both next and previous nodes
- **Circular Linked List**: Last node points back to first node
- **Skip List**: Hierarchical linked list with multiple layers for faster searching

### Find Middle Node (Fast/Slow Pointer)
```c
struct Node* findMiddle(struct Node* head) {
    struct Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

### Merge Two Sorted Lists
```c
struct Node* mergeSorted(struct Node* l1, struct Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    struct Node* result = NULL;
    
    if (l1->data <= l2->data) {
        result = l1;
        result->next = mergeSorted(l1->next, l2);
    } else {
        result = l2;
        result->next = mergeSorted(l1, l2->next);
    }
    
    return result;
}
```

### Check if Palindrome
```c
bool isPalindrome(struct Node* head) {
    // Find middle
    struct Node *slow = head, *fast = head;
    struct Node *prev = NULL;
    
    // Reverse first half while finding middle
    while (fast && fast->next) {
        fast = fast->next->next;
        struct Node* temp = slow->next;
        slow->next = prev;
        prev = slow;
        slow = temp;
    }
    
    // If odd length, skip middle node
    if (fast) slow = slow->next;
    
    // Compare reversed first half with second half
    while (prev && slow) {
        if (prev->data != slow->data) return false;
        prev = prev->next;
        slow = slow->next;
    }
    
    return true;
}
```

### Reverse in Groups of K
```c
struct Node* reverseK(struct Node* head, int k) {
    if (!head || k == 1) return head;
    
    struct Node *current = head;
    struct Node *next = NULL;
    struct Node *prev = NULL;
    int count = 0;
    
    // Reverse first k nodes
    while (current && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    
    // Recursively reverse rest of the list
    if (next) head->next = reverseK(next, k);
    
    return prev;
}
```

---
Next: [[Arguments]]