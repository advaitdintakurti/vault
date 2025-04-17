Merge sort is a sorting algorithm that uses the divide-and-conquer strategy:
1. Divide the array into two halves.
2. Recursively sort each half.
3. Merge the sorted halves.

![[mergesort.png|400]]

> **Algorithm:**
>     If array size is 1:
>         Array is already sorted
>     Else:
>         Break into left and right halves
>         Merge sort each half individually

### Implementation

Top down implementation of merge sort.

- Recursively splits the array until single elements are reached.
- Merges sorted arrays back up.

### Pseudocode
```c
function mergeSort(arr)
    if length of arr <= 1
        return arr
    
    mid = length of arr // 2
    left = mergeSort(arr[0 to mid-1])
    right = mergeSort(arr[mid to end])
    
    return merge(left, right)

function merge(left, right)
    result = empty array
    i = 0, j = 0
    
    while i < length of left and j < length of right
        if left[i] <= right[j]
            append left[i] to result
            i = i + 1
        else
            append right[j] to result
            j = j + 1
    
    // Append remaining elements
    while i < length of left
        append left[i] to result
        i = i + 1
    
    while j < length of right
        append right[j] to result
        j = j + 1
    
    return result
```

#### Merge function

Combines two sorted subarrays into a single sorted array:

```c
void merge(int arr[], int start, int mid, int end) {
    int size = end - start + 1;
    int temp[size]; // Single temporary array
    int i = start, j = mid + 1, k = 0;

    // Merge elements from both halves into the temporary array
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements from the left half
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements from the right half
    while (j <= end) {
        temp[k++] = arr[j++];
    }

    // Copy sorted elements back to the original array
    for (i = 0; i < size; i++) {
        arr[start + i] = temp[i];
    }
}
```

#### Merge sort function

Recursively sorts the array.

```c
void mergesort(int arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
```


### Complexity Calculations:
```
T(n) = T(n/2) + T(n/2) + kn
        = T(n/4) + T(n/4) + k(n/2) + T(n/4) + T(n/4) + k(n/2) + kn
        = 4T(n/4) + 2kn
        = 8T(n/8) + 3kn
        = 16T(n/16) + 4kn
        ...
        = 2^i * T(n/2^i) + ikn
        ...
        = nT(n/n) + knlogn
        = nT + knlogn
        ~ O(nlogn)
```

## Key Properties

- **Time Complexity**: `O(nlogn⁡)` in all cases (best, worst, average).
- **Space Complexity**: `O(n)`
- **Stability**: Preserves the order of equal elements.
- **Not In-Place**: Requires extra memory for temporary arrays.

---

### k-way merge sort vs two-way merge sort

advantages of k-way merge sort
-> more efficient with large datasets
-> more scalable
-> more flexible

disadvantages
-> harder to implement
-> higher space requirements (same complexity though)
-> overkill for small datasets