## Sets

A **set** is a collection of unique elements where the order does not matter.

#### Key Operations on Sets:

- Adding an element
- Removing an element
- Checking for membership

### Array Implementation

- Store elements in an array.
- Ensure that no duplicate elements are added by checking before insertion.

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int elements[MAX_SIZE];
    int size;
} Set;

// Initialize the set
void initSet(Set *set) {
    set->size = 0;
}

// Check if an element is in the set
bool contains(Set *set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == value) {
            return true;
        }
    }
    return false;
}

// Add an element to the set
void add(Set *set, int value) {
    if (!contains(set, value)) {
        if (set->size < MAX_SIZE) {
            set->elements[set->size++] = value;
        } else {
            printf("Set is full!\n");
        }
    }
}

// Print the set
void printSet(Set *set) {
    for (int i = 0; i < set->size; i++) {
        printf("%d ", set->elements[i]);
    }
    printf("\n");
}

int main() {
    Set set;
    initSet(&set);
    add(&set, 10);
    add(&set, 20);
    add(&set, 10); // Duplicate, won't be added
    printSet(&set); // Output: 10 20
    return 0;
}
```

### Bitmasking Implementation

- If the set elements are small integers, you can use a single integer or array of bits as a bitmask.
- Each bit represents whether a specific element is in the set.

Example for a set of integers from 0 to 31:
```c
#include <stdio.h>
#include <stdbool.h>

typedef unsigned int BitSet;

void add(BitSet *set, int value) {
    *set |= (1 << value);
}

void remove(BitSet *set, int value) {
    *set &= ~(1 << value);
}

bool contains(BitSet set, int value) {
    return set & (1 << value);
}

int main() {
    BitSet set = 0; // Empty set
    add(&set, 3);   // Add 3
    add(&set, 5);   // Add 5
    remove(&set, 3); // Remove 3
    
    printf("Contains 3? %s\n", contains(set, 3) ? "Yes" : "No"); // Output: No
    printf("Contains 5? %s\n", contains(set, 5) ? "Yes" : "No"); // Output: Yes
    return 0;
}
```

## Maps

A **map** (also called a dictionary or associative array) is a collection of key-value pairs, where each key is unique, and each key is associated with a value.

#### Key Operations on Maps:

- Inserting a key-value pair
- Removing a key-value pair
- Looking up a value by its key

### Array Implementation

- Store the key-value pairs in an array of structs.
- Linear search for operations.

```c
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char key[50];
    int value;
} MapEntry;

typedef struct {
    MapEntry entries[MAX_SIZE];
    int size;
} Map;

// Initialize the map
void initMap(Map *map) {
    map->size = 0;
}

// Add a key-value pair
void put(Map *map, const char *key, int value) {
    for (int i = 0; i < map->size; i++) {
        if (strcmp(map->entries[i].key, key) == 0) {
            map->entries[i].value = value; // Update existing key
            return;
        }
    }
    if (map->size < MAX_SIZE) {
        strcpy(map->entries[map->size].key, key);
        map->entries[map->size++].value = value;
    }
}

// Get the value associated with a key
int get(Map *map, const char *key) {
    for (int i = 0; i < map->size; i++) {
        if (strcmp(map->entries[i].key, key) == 0) {
            return map->entries[i].value;
        }
    }
    return -1; // Key not found
}

int main() {
    Map map;
    initMap(&map);
    put(&map, "Alice", 30);
    put(&map, "Bob", 25);
    printf("Alice's age: %d\n", get(&map, "Alice")); // Output: 30
    printf("Bob's age: %d\n", get(&map, "Bob"));     // Output: 25
    return 0;
}
```