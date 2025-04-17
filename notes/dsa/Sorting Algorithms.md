[[Basic Sorting Algorithms]]
[[Quicksort]]
[[dsa/Merge Sort|Merge Sort]] 

---
### Quicksort vs Merge Sort

-> Quicksort uses a pivot element to partition the array
-> Merge sort partitions the array into two halves until each half contains one element

-> Quicksort is an **unstable sorting algorithm**, meaning it can **change the order of equal elements**
-> Merge sort is a **stable sorting algorithm**, meaning it **preserves the order of equal elements**

-> Quicksort is **in-place**, and hence requires minimal extra space
-> Merge sort requires extra space for merging subarrays

-> Quicksort can have **O(n<sup>2</sup>)** time complexity if pivot is chosen poorly, but otherwise is O(nlogn)
-> Merge sort always has **O(nlogn)** time complexity

-> Quick sort is better on smaller datasets / when system memory is limited
-> Merge sort is better on larger datasets / linked lists / if we want to preserve order of equal elements



