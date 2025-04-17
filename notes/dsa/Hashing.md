
A hash table is a data structure that stores key-value pairs. It uses a hash function to map keys to indices in an array, enabling efficient insertion, deletion, and search operations. 

### Hash Functions

A hash function maps keys to indices in the hash table. The hash function must have specific properties:
- It must be deterministic, ensuring the same key always maps to the same index.
- It should be computationally efficient.
- It must distribute keys uniformly, to reduce collisions.

**Example:**
```c
unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash += *str++;
    }
    return hash % TABLE_SIZE;
}
```


### Hash Table Implementation

#### Hash Table Array:

 - An array of `Entry` structures, where each entry stores a key-value pair.
 - The hash function determines the index in the array where the key-value pair should be stored.
 
#### Insertion:

 - Calculates the hash value for the key.
 - Checks if the corresponding slot in the array is empty.
 - If empty, inserts the key-value pair into the slot.
 - If not empty, a collision occurs. In this simple implementation, it prints a warning and returns `false`.
 
#### Search:

 - Calculates the hash value for the key.
 - Checks if the key-value pair is present at the corresponding index in the array.
 - Returns the value if found, otherwise returns `-1`.
 
#### Deletion:

 - Calculates the hash value for the key.
 - Checks if the key-value pair is present at the corresponding index in the array.
 - If found, frees the memory allocated for the key and the entry.

**Implementation:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct {
    char *key;
    int value;
} Entry;

Entry *table[TABLE_SIZE];

// Hash function to map keys to indices in the hash table
unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash += *str++;
    }
    return hash % TABLE_SIZE;
}

// Insert a key-value pair into the hash table
bool insert(const char *key, int value) {
    int index = hash(key);
    if (table[index] == NULL) {
        table[index] = (Entry*)malloc(sizeof(Entry));
        table[index]->key = strdup(key);
        table[index]->value = value;
        return true;
    } else {
        // Collision detected, handle it (e.g., print a warning)
        printf("Collision detected for key: %s\n", key);
        return false;
    }
}

// Search for a key in the hash table and return its value
int search(const char *key) {
    int index = hash(key);
    if (table[index] != NULL && strcmp(table[index]->key, key) == 0) {
        return table[index]->value;
    }
    return -1; // Key not found
}

// Delete a key-value pair from the hash table
void delete(const char *key) {
    int index = hash(key);
    if (table[index] != NULL && strcmp(table[index]->key, key) == 0) {
        free(table[index]->key);
        free(table[index]);
        table[index] = NULL;
    }
}

int main() {
    insert("apple", 10);
    insert("banana", 20);
    insert("cherry", 30);
    insert("date", 40);
    insert("elderberry", 50); // This will cause a collision

    printf("Value of apple: %d\n", search("apple"));
    printf("Value of date: %d\n", search("date"));

    delete("banana");

    printf("Value of banana after deletion: %d\n", search("banana"));

    return 0;
}
```

### Collision Handling

A hash table maps keys to indices in an array using a hash function. However, it's possible for two different keys to hash to the same index, resulting in a collision. Without proper collision handling, this can lead to data loss or incorrect results.

Collision handling techniques like open addressing and separate chaining are essential to ensure efficient and reliable operation of hash tables.

### Collision Handling: Open Addressing

In open addressing, all key-value pairs are stored in the hash table itself. Collisions are resolved by probing for the next available slot.

The data structure for an entry in the table is defined as:

```c
typedef struct {
    char *key;
    int value;
} Entry;

Entry *table[TABLE_SIZE];
```

#### Insertion

To insert a key-value pair:
1. Compute the hash value for the key.
2. If the computed slot is empty, store the pair there.
3. If the slot is occupied, probe sequentially until an empty slot is found.

```c
bool insert(const char *key, int value) {
    int index = hash(key);
    while (table[index] != NULL) {
        if (strcmp(table[index]->key, key) == 0) {
            table[index]->value = value;
            return true;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    table[index] = (Entry*)malloc(sizeof(Entry));
    table[index]->key = strdup(key);
    table[index]->value = value;
    return true;
}
```

#### Search

To find a key:
1. Compute the hash value.
2. Probe the table starting at the computed index until the key is found or an empty slot is encountered.

```c
int search(const char *key) {
    int index = hash(key);
    while (table[index] != NULL) {
        if (strcmp(table[index]->key, key) == 0) {
            return table[index]->value;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return -1; // Key not found
}
```

#### Deletion

To delete a key:
1. Locate the key using the search function.
2. Free the memory and mark the slot as deleted.

```c
void delete(const char *key) {
    int index = hash(key);
    while (table[index] != NULL) {
        if (strcmp(table[index]->key, key) == 0) {
            free(table[index]->key);
            free(table[index]);
            table[index] = DELETED;
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }
}
```

### Collision Handling: External Chaining

In external chaining, collisions are resolved by maintaining a linked list at each index of the hash table. Each index stores a pointer to the head of a linked list containing all entries with the same hash value.

The structure for a linked list node is:

```c
typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

Node *table[TABLE_SIZE];
```

#### Insertion

To insert a key-value pair:
1. Compute the hash value for the key.
2. Create a new node and insert it at the beginning of the linked list at the corresponding index.

```c
bool insert(const char *key, int value) {
    int index = hash(key);
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
    return true;
}
```

#### Search

To search for a key:
1. Compute the hash value.
2. Traverse the linked list at the corresponding index until the key is found or the end is reached.

```c
int search(const char *key) {
    int index = hash(key);
    Node *temp = table[index];
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1; // Key not found
}
```

#### Deletion

To delete a key:
1. Locate the key by traversing the linked list.
2. Remove the corresponding node from the list.

```c
void delete(const char *key) {
    int index = hash(key);
    Node *temp = table[index], *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            if (prev == NULL) {
                table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp->key);
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}
```

### Additional Notes

- **Load Factor:** The load factor, defined as the ratio of the number of elements to the table size, affects performance. Rehashing is often performed when the load factor exceeds a threshold.
- **Rehashing:** Involves resizing the table and reinserting elements using the hash function to improve performance.
- **Memory Management:** Proper memory allocation and deallocation are crucial in C to avoid memory leaks and undefined behavior.
- **Collision Handling:** Choosing the appropriate collision resolution strategy depends on the use case and memory constraints.
