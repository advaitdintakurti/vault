
### Selection Sort

Selection Sort is a simple comparison-based sorting algorithm. It works by dividing the input list into two parts: the sorted part at the beginning and the unsorted part at the end. It repeatedly selects the smallest element from the unsorted part and swaps it with the first element of the unsorted part, thereby extending the sorted part by one element.

#### Steps:

1. Start with the first element of the array.
2. Find the smallest element in the unsorted portion of the array.
3. Swap it with the element at the current position.
4. Move to the next element and repeat the process until the entire array is sorted.

#### Implementation:
```c
int arr[] = {4, 7, 5, 3, 2, 1}; // Initial array

// Implementing Selection Sort
for(int i = 0; i < 6 - 1; i++) {
    int min_idx = i;
    for(int j = i + 1; j < 6; j++) {
        if(arr[j] < arr[min_idx]) {
            min_idx = j;
        }
    }
    // Swap the found minimum element with the first element
    int temp = arr[min_idx];
    arr[min_idx] = arr[i];
    arr[i] = temp;
}

// Sorted: {1, 2, 3, 4, 5, 7}

```
#### Iterations:
```latex
Iteration 1: {1, 7, 5, 3, 2, 4} 
Iteration 2: {1, 2, 5, 3, 7, 4}
Iteration 3: {1, 2, 3, 5, 7, 4}
Iteration 4: {1, 2, 3, 4, 7, 5}
Iteration 5: {1, 2, 3, 4, 5, 7}
```
#### Complexity:

- **Time Complexity**: O(n²) in all cases, as it always makes the same number of comparisons.
- **Space Complexity**: O(1) because it is an in-place sort.

### Bubble Sort

Bubble Sort is another simple comparison-based sorting algorithm. It works by repeatedly stepping through the list, comparing adjacent pairs of elements, and swapping them if they are in the wrong order. The largest element "bubbles up" to its correct position at the end of the list on each pass through the list.

#### Steps:
1. Compare each pair of adjacent elements in the array.
2. If the pair is in the wrong order (the first is greater than the second), swap them.
3. Repeat the process for each element, except the last one on each pass (as it's already in place).
4. Continue until no swaps are needed, meaning the array is sorted.

#### Implementation:
```c
int arr[] = {5, 3, 4, 2}; // Initial array

// Implementing Bubble Sort
for(int i = 0; i < 4 - 1; i++) {
    for(int j = 0; j < 4 - i - 1; j++) {
        if(arr[j] > arr[j + 1]) {
            // Swap arr[j] and arr[j + 1]
            int temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
    }
}

// Sorted: {2, 3, 4, 5}
```

#### Iterations:
```latex
Iteration 1: {3, 5, 4, 2}
Iteration 2: {3, 4, 5, 2}
Iteration 3: {3, 4, 2, 5}
Iteration 4: {3, 2, 4, 5}
Iteration 5: {2, 3, 4, 5}
```
#### Complexity:

- **Time Complexity**:
    - Worst and Average Case: O(n²) (when the array is in reverse order or unordered)
    - Best Case: O(n) (when the array is already sorted)
- **Space Complexity**: O(1) because it is an in-place sort.

### Insertion Sort

Insertion Sort is a comparison-based sorting algorithm that builds the final sorted array one element at a time. It works similarly to the way you might sort playing cards in your hands. You take one element and insert it into its correct position in the already sorted part of the array.

#### Steps:

1. Start from the second element (assume the first element is already sorted).
2. Compare the current element with the sorted part of the array.
3. Shift all the elements in the sorted part that are greater than the current element to one position ahead.
4. Insert the current element into its correct position.
5. Repeat the process for each element in the array.

#### Implementation:
```c
int arr[] = {6, 7, 9, 12, 8}; // Initial array

for(int i = 1; i < 5; i++) {
    int key = arr[i];
    int j = i - 1;

    // Move elements of arr[0..i-1], that are greater than key, to one position ahead
    while(j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j = j - 1;
    }
    arr[j + 1] = key;
}

// Sorted: {6, 7, 8, 9, 12}

```

#### Implementation:
```latex
Iteration 1: {6, 7, 9, 12, 8} // Initial state, no change needed
Iteration 2: {6, 7, 9, 12, 8} // Initial state, no change needed
Iteration 3: {6, 7, 9, 12, 8} // Initial state, no change needed
Iteration 4: {6, 7, 8, 9, 12} // Insert 8 into correct position
```
#### Complexity:
- **Time Complexity**:
    - Worst and Average Case: O(n²) (when the array is in reverse order or unordered)
    - Best Case: O(n) (when the array is already sorted)
- **Space Complexity**: O(1) because it is an in-place sort.


### Comparision:
- **Selection Sort** is best for small datasets or when memory is limited, but it's not stable.
- **Bubble Sort** is educational for learning, but inefficient for large datasets.
- **Insertion Sort** is useful for nearly sorted arrays or small datasets and is stable.

---
Next: [[Pointers]]