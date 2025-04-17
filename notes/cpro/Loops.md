Loops in C are used to repeatedly execute a block of code as long as a specified condition is true. The two most common loops are `while` and `for`.

### `while` Loop

The `while` loop continues to execute as long as the condition remains true. It checks the condition before each iteration.
```c
while (condition) {
    // Code to be executed
}
```

#### Example:
```c
int count = 0;
while (count < 5) {
    printf("Count: %d\n", count);
    count++;
}
```

### `for` Loop

The `for` loop is typically used when the number of iterations is known. It includes initialization, condition, and increment/decrement in a single line.

```c
for (initialization; condition; increment) {
    // Code to be executed
}
```

#### Example:
```c
for (int i = 0; i < 5; i++) {
    printf("i: %d\n", i);
}
```

### Comparison

- **`while` Loop**:
    - Best when the number of iterations isn't known in advance.
    - Condition is evaluated before the loop body executes.
    
- **`for` Loop**:
    - Best when the number of iterations is known or easily defined.
    - Combines initialization, condition, and increment/decrement in one line, making the loop structure concise.

### `break` Statement
The `break` statement is used to exit a loop prematurely. When encountered, it immediately terminates the nearest enclosing loop, and control is transferred to the code following the loop.
```c
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break; // Exit the loop when i equals 5
    }
    printf("%d\n", i);
}
```

### `continue` Statement
The `continue` statement skips the remaining code in the current iteration of a loop and immediately proceeds to the next iteration. It does not terminate the loop, just the current iteration.
```c
for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        continue; // Skip even numbers
    }
    printf("%d\n", i);
}
```

---
Next: [[Conditional Operators]]