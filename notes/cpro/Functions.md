A function is a self-contained block of code that performs a specific task.
```
<return_type> function_name(<parameter_list>) {
    // Function body
}
```

Example:
```c
int sum(int a, int b) {
  return a + b;
}
```
### Function Declaration (Prototype)

Function declarations, also known as prototypes, tell the compiler about the function's name, return type, and parameters before defining or calling it.

### Call by Value vs. Call by Reference

In C, functions can be called either **by value** or **by reference**, depending on how arguments are passed.

#### Call by Value

In **call by value**, a copy of the actual argument's value is passed to the function. Modifying the parameters inside the function does not affect the original arguments.
- **Pros**: The original data is safe from modification.
- **Cons**: If the data being passed is large (like arrays or structures), it can be inefficient.
```c
int sum(int a, int b) {
    return a + b;
}

int main() {
    int x = 5, y = 10;
    int result = sum(x, y);
    // x and y remain unchanged
    return 0;
}
```
#### Call by Reference

In **call by reference**, the memory address of the actual argument is passed to the function. This allows the function to modify the original argument’s value.
```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5;
    int y = 10;

    swap(&x, &y);  // Pass the memory addresses of x and y
    // x = 10, y = 5 (values are swapped)
    
    return 0;
}
```

### Passing Arrays to Functions

In C, arrays are always passed **by reference** to functions because the name of the array represents the address of its first element.
```c
void arrayOperation(int arr[], int n) {
    // Function to process the array
    for (int i = 0; i < n; i++) {
        // Do something with arr[i]
    }
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    processArray(arr, 5);  // Passing array to function
    return 0;
}
```
Since arrays are passed by reference, the function operates on the original array.

**Example: Sum of Array Elements**
```c
float sum(int n; int arr[]) {
  float ans;
  // sum all elements of array
  return ans;
}

int main() {
  int n = 5;
  int arr[5] = [0,4,3,2,6];
  return sum(n, arr)
}
```

### Returning Values from a Function

Functions in C can return a single value to the calling function. The return value is specified using the `return` keyword.
```c
int multiply(int a, int b) {
    return a * b;  // Returns the product of a and b
}
```

If a function does not need to return a value, its return type should be `void`.
```c
void printMessage() {
    printf("Hello, World!");
}
```

### Scope and Lifetime of Variables in Functions

**Local Variables**: Variables declared inside a function are local to that function and cannot be accessed outside it. They are created when the function is called and destroyed when the function exits.
```c
void test() {
    int x = 10;  // Local variable
}
```

**Global Variables:** Variables declared outside all functions are global variables and can be accessed by any function in the program. They remain in memory throughout the program's execution.
```c
int global = 100;  // Global variable

void func() {
    printf("%d", global);  // Accessible here
}

void tion() {
    globalVar = 200;  // Can modify the global variable
}
```

### Inline functions
The `inline` keyword is a suggestion to the compiler that a function should be expanded inline rather than a regular function call being generated. This can improve performance by eliminating the overhead of a function call.

### Function Pointers

---
Next: [[Recursion]]