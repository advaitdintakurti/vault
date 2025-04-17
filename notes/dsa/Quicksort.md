Quicksort is a **divide-and-conquer** algorithm for sorting. It is efficient for large datasets and widely used in practice due to its average-case performance.

![[quicksort.png|700]]

```
If array length is 1:
    return
Else:
    pick a *pivot*
    partition array about pivot
    recursively quicksort both partitions
    return
```


#### Picking a pivot

**First/Last Element:**
-> Simple to implement.
-> **Worst-case:** Occurs when the array is already sorted or reverse sorted, leading to highly unbalanced partitions.

**Random Element:**
-> Reduces the chance of worst-case scenarios.
-> Increases randomness in partitions.

**Median of Three:**
-> Choose the median of the first, middle, and last elements.
-> Provides a better partitioning, reducing the likelihood of worst-case performance.

#### Partitioning about the pivot

Once we have our pivot, we can partition the elements of the array such that:
-> All elements smaller than the pivot are to its left
-> All elements greater than the pivot are to its right

### Pseudocode
```c
Swap(int* a int* b)
    temp = *a;
    *a = *b;
    *b = temp;
End

Partition(arr, low, high)
    // Choose last element as pivot
    pivot = arr[high]
    
    // Initialize index of smaller element
    i = (low - 1)

    For j From low To (high - 1) Do
        If arr[j] < pivot Then
            Increment i By 1
            
            // Swap elements at indices i and j if arr[j] is smaller than pivot
            Swap(&arr[i], &arr[j])
        End If
    End For
        
    // Swap the found smaller element with the pivot at index 'i+1'
    Swap(&arr[i + 1], &arr[high])
    
    Return (i + 1) // Return index of pivot
    
End

QuickSort(arr, low, high)
    If low < high Then
        pivotIndex = Partition(arr, low, high)
        QuickSort(arr, low, pivotIndex - 1)
        QuickSort(arr, pivotIndex + 1, high)
    End If
End
```

> In this implementation, last element is picked as pivot.
```c
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
```

1. **Choose a Pivot**: The function selects the last element in the array segment as the pivot.

2. **Initialize Index**: It initializes an index `i` to keep track of the position where the next smaller element should go. Initially, `i` is set to one position before the start of the segment (`low - 1`).

3. **Rearrange Elements**: The function iterates through the array segment from `low` to `high - 1`. For each element:
    - If the element is smaller than the pivot, it increments `i` and swaps the element with the element at index `i`.
    
4. **Place Pivot in Correct Position**: After the loop, the pivot element is swapped with the element at index `i + 1`. This places the pivot in its correct sorted position.

5. **Return Pivot Index**: The function returns the index of the pivot element, which is now in its correct position.

#### Quicksort function

```c
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}
```

## Complexity Analysis

**Worst Case:**
```
T(n) = T(n-1) + T(0) + c(n-1)
T(n) = T(n-2) + 2T(0) + c(n-1 + n-2)
...
T(n) = T(0) + nT(0) + nc + c(n(n-1)/2)
     ~ n + n^2
     ~ O(n^2)
```

**Best case:**
```
T(n) = 2T(n/2) + cn
T(n) = 4T(n/4) + 2cn
...
T(n) ~ Ω(nlogn)
```

**Average Case:**
```
T(n) = Θ(nlogn)
```

#### Space Complexity
-> **In-place Partitioning:** Quicksort does not require additional space for array storage.
-> **Auxiliary Space:** `O(logn)` in the call stack (recursion).

## Pro/Con Analysis

**Advantages:**
-> **Efficient:** Average case is `O(nlogn)`.
-> **In-place:** Requires no additional space beyond recursion stack.
-> **Tailorable:** Pivot selection can be optimized for the dataset.

**Disadvantages:**
-> **Worst-case Performance:** `O(n^2)`, though rare with good pivot selection.
-> **Not Stable:** Does not preserve the relative order of equal elements.

