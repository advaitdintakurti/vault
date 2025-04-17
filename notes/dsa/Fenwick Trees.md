
A **Fenwick Tree** (or **Binary Indexed Tree, BIT**) is a data structure for efficiently computing prefix sums and performing point updates in an array.

Given an array `A[1...n]`, a Fenwick Tree supports:  
- **Point updates** (modify an element at index `i`) in **O(log n)**.  
- **Prefix sum queries** (sum of elements from `1` to `i`) in **O(log n)**.  
- **Range sum queries** (sum from `l` to `r`) in **O(log n)**.  

Instead of storing individual elements, **each node stores the cumulative sum of a segment** determined by **the rightmost set bit in the index**.


Each index `i` in `BIT` represents a segment of elements in `A`, covering a range of size `2^r`, where `r` is the lowest set bit in `i`.  

- **Parent of `i`**: Clear the last set bit  
```
parent(i) = i - (i & -i)
```

- **Next index to update**: Add the last set bit  
```
next(i) = i + (i & -i)
```

---

## Operations  

#### Updating an Element (Point Update)  
- Update the tree when an element `A[i]` changes.  
- Traverse upwards, updating all affected nodes using `i + (i & -i)`.  

#### Prefix Sum Query  
- Computes `sum(A[1] ... A[i])` efficiently.  
- Traverse `BIT` by decrementing `i` using `i - (i & -i)`.  

#### Range Sum Query  
```
range_sum(l, r) = prefix_sum(r) - prefix_sum(l - 1)
````

#### Constructing the Fenwick Tree  
- Start with an empty `BIT` and insert elements one by one using `update()`.  

#### Finding the K-th Smallest Element (Binary Lifting)  
- Used in frequency-based BIT structures for **ordered frequency queries**.  
- Uses **binary search** on `BIT` to locate an index corresponding to a given prefix sum.

```c
#include <stdio.h>

#define MAXN 1000

int BIT[MAXN + 1], A[MAXN + 1], n;

// Update BIT at index i by adding value
void update(int i, int value) {
    while (i <= n) {
        BIT[i] += value;
        i += (i & -i);
    }
}

// Compute prefix sum from 1 to i
int prefixSum(int i) {
    int sum = 0;
    while (i > 0) {
        sum += BIT[i];
        i -= (i & -i);
    }
    return sum;
}

// Compute sum in range [l, r]
int rangeSum(int l, int r) {
    return prefixSum(r) - prefixSum(l - 1);
}

// Build Fenwick Tree from initial array
void build() {
    for (int i = 1; i <= n; i++)
        update(i, A[i]); // Initialize BIT with array values
}

// Find the k-th smallest element (binary lifting)
int findKth(int k) {
    int sum = 0, pos = 0;
    for (int i = 1 << 10; i > 0; i >>= 1) {
        if (pos + i <= n && sum + BIT[pos + i] < k) {
            sum += BIT[pos + i];
            pos += i;
        }
    }
    return pos + 1;
}

int main() {
    n = 6;
    int arr[] = {0, 3, 2, -1, 6, 5, 4}; // 1-based indexing

    for (int i = 1; i <= n; i++)
        A[i] = arr[i];

    build();

    printf("Sum of first 4 elements: %d\n", prefixSum(4)); // Output: 10
    printf("Sum of range [2, 5]: %d\n", rangeSum(2, 5)); // Output: 12

    update(3, 3); // Modify A[3] by adding 3
    printf("Sum after update: %d\n", prefixSum(4)); // Output: 13

    return 0;
}
````