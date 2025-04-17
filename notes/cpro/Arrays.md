Collection of like items stored at contiguous memory locations.
![[array.png]]

```c
// data_type array_name [size];
int a[5] = {1,2,4,8,16}; 
```

Array size can be skipped if an initializer list is used.
```c
int b[] = {9,8,7,6}
```
Here, the compiler infers the length of array from the initializer list.

Array elements can be accessed as `a[i]`
```c
printf("%d", a[2]) // Output: 4
```

### Memory address
`&a[0]` refers to the memory address of  the first element of the array `a`.
`a[0]` refers to the element stored at that memory address.

### Multidimensional arrays
Multidimensional arrays are essentially arrays of arrays:
```c
int arr[3][3] = {{1,2,3},
                 {4,5,6},
                 {7,8,9}};
```

### Inferred Length
For one-dimensional arrays, the size can be inferred by the compiler:
```c
int arr[] = {3, 4, 5, 6, 7, 8}; // initialized with 6 elements
```
For multidimensional arrays, only the first dimension can be inferred:
```c
int arr[][4] = {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10, 11, 12}
};
```

### Scan elements of array
```c
// one dimensional
for(int i = 0; i < 5; i++) {
  scanf("%d", &a[i]);
}

// two dimensional
for(int i = 0; i < 5; i++) {
  for(int j = 0; j < 5; j++) {
    scanf("%d", &a[i][j]);
  }
}
```

### Reverse the elements of an array
```c
int arr[5] = {10, 4, 7, 6, 2};

for (int i = 0; i < 2; i++) {
  arr[i] = arr[i] + arr[4 - i] - (arr[4 - i] = arr[i]);
}

for (int i = 0; i < 5; i++) {
  printf("%d ", arr[i]);
}

// Output: 2 6 7 4 2
```

### Leaders of an array
An element is called a *leader* if it is greater than all elements to its right.

```c
int arr[5] = {7, 10, 1, 2, 6};
int leader = arr[4];
printf("%d\n", leader);

for (int i = 4; i > -1; i--) {
  if (arr[i] > leader) {
    leader = arr[i];
    printf("%d\n", leader);
  }
}

// Output: 10 6
```

### Check contiguous sum

`(v1)`
```c
#include <stdio.h>

int main() {
  unsigned int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  int sum;
  scanf("%d", &sum);

  for (int i = 0; i < 10; i++) {
    int current_sum = arr[i];
    if (current_sum == sum) {
      printf("%d", arr[i]);
      return 0;
    }
    for (int j = i + 1; j < 10; j++) {
      current_sum = current_sum + arr[j];
      if (current_sum == sum) {
        printf("%d %d", arr[i], arr[j]);
        return 0;
      }
    }
  }
}
```

### Maximum contiguous sum of a subarray
```c
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int cur_max = arr[0];
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum = sum + arr[i];
        if (cur_max < sum) {
            cur_max = sum;
        }
        if (sum < 0) {
            sum = 0;
        }
    }

    printf("%d", cur_max);

    return 0;
}
```

### Maximum contiguous product
```c
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int res = arr[0];
    int max_prod = arr[0];
    int min_prod = arr[0];

    for (int i = 1; i < n; i++) {
      if(arr[i] < 0) {
	int temp = max_prod;
	max_prod = min_prod;
	min_prod = temp;
      }

      max_prod = (arr[i] > max_prod * arr[i]) ? arr[i] : arr[i] * max_prod;
      min_prod = (arr[i] < min_prod * arr[i]) ? arr[i] : arr[i] * min_prod;

      if(max_prod > res) res = max_prod;
    }

    printf("%d", res);

    return 0;
}
```

### Memory Address
```c
char arr[10][15]
```
Base address of `arr[0][0]` is `100`

### Order
**Row Major Order:** Move row-wise (`a[0][0] -> ... -> a[0][14] -> a[1][0]`)
**Column Major Order:** Move column-wise (`a[0][0] -> ... -> a[7][0] -> a[1][0]`)


---
Next: [[Basic Sorting Algorithms]]