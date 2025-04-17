

```c
int func() {
  while(1) {
    func();
  }
}
```

Recursion in C refers to the process where a function calls itself, directly or indirectly, to solve a problem. It typically involves two parts:

1. **Base Case**: A condition that stops the recursion to prevent infinite loops. This is essential for terminating the recursive calls.
    
2. **Recursive Case**: The function calls itself with modified arguments, gradually moving towards the base case.

#### Example 1: Factorial Function

The factorial of a number `n` is the product of all integers from 1 to `n`. A recursive function to calculate factorial can be written as:

```c
#include <stdio.h>

int factorial(int n) {
    if (n == 0) {  // Base case: factorial of 0 is 1
        return 1;
    }
    return n * factorial(n - 1);  // Recursive case
}

int main() {
    int num = 5;
    printf("%d! = %d", num, factorial(num));
    return 0;
}
```

**Explanation:**
- The function calls itself with `n-1` until `n` becomes 0, at which point it returns 1.
- The recursive calls then "unwind," multiplying the returned values to compute the final result.

#### Example 2: Fibonacci Sequence

The Fibonacci sequence is defined as:

- `F(0) = 0`
- `F(1) = 1`
- `F(n) = F(n-1) + F(n-2)`, for `n > 1`

```c
#include <stdio.h>

int fibonacci(int n) {
    if (n == 0)  // Base case 1
        return 0;
    if (n == 1)  // Base case 2
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);  // Recursive case
}

int main() {
    int num = 10;
    printf("Fibonacci of %d is %d\n", num, fibonacci(num));
    return 0;
}
```

**Explanation:**
- The function keeps calling itself to compute the sum of the previous two Fibonacci numbers.
- The base cases `n == 0` and `n == 1` stop further recursion.

### Backtracking
Backtracking is a general algorithmic technique that considers searching every possible combination in order to solve a computational problem. It is often used to solve problems that involve finding a set of solutions that satisfy a set of constraints.

### Example 3: Print all permutations of a string

> O(n\*n!)
```c
#include <stdio.h>
#include <string.h>

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);
    } else {
        for (int i = left; i <= right; i++) {
            swap(&str[left], &str[i]);
            permute(str, left + 1, right);
            swap(&str[left], &str[i]);
        }
    }
}

int main() {
    char str[100];
    scanf("%s", str);
    int n = strlen(str);
    permute(str, 0, n - 1);
    return 0;
}
```

---
Next: [[Structures]]
