```c
int binsearch(int arr[], int low, int high, int x) {
    while(low <= high) {
        int mid = (low+high)/2;

        // element found in the middle
        if(arr[mid] == x) return mid;

        // shrink search area
        if(arr[mid] < x) low = mid + 1;

        // shrink search area
        if(arr[mid] > x) high = mid - 1;
    }

    // if control reaches here, element was not found :(
    return -1;
}
```

#### Question: Will using binary search help improve insertion sort?

If we used binary search in insertion sort, the complexity is O(n^2) in every case, as opposed to only in the worst case.