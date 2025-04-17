`if/else` statements are used to execute code blocks based on specific conditions. They allow your program to make decisions and branch its execution.

```c
if (condition) {
    // Code to be executed if condition is true
} else {
    // Code to be executed if condition is false
}
```


The `if` statement evaluates a condition, and if the condition is true, it executes the code block.
```c
int age = 17;
if (age >= 18) {
    printf("You are an adult.\n");
}
```

When the condition is false, the `else` code block is executed.
```c
int age = 17;
if (age >= 18) {
    printf("You are an adult.\n");
} else {
    printf("You are a minor.\n");
}
```

#### `if/else if/else` Statement

The `if/else if/else` structure allows for multiple conditions to be checked sequentially.
```c
if (condition1) {
    // Code to be executed if condition1 is true
} else if (condition2) {
    // Code to be executed if condition2 is true
} else {
    // Code to be executed if both conditions are false
}

```

#### Nested `if` Statements

`if` statements can be nested within each other to handle more complex decision-making.
```c
int age = 17;
int hasID = 1;

if (age >= 18) {
    if (hasID) {
        printf("You can enter.\n");
    } else {
        printf("You need an ID to enter.\n");
    }
} else {
    printf("You are too young to enter.\n");
}

```

### Logical Operators
Logical operators are used to combine multiple conditions in decision-making structures like `if` statements. The two primary logical operators in C are `||` (OR) and `&&` (AND).

#### `||` (Logical OR)
The `||` operator returns `true` if at least one of the conditions is true.

#### `&&` (Logical AND)
The `&&` operator returns `true` only if both conditions are true. It is used when all specified conditions must be met to execute a block of code.

#### Example:
```c
int age = 17;
int hasID = 1;

if ((age >= 18 && hasID) || age >= 21) {
    printf("You can enter.\n");
} else {
    printf("You cannot enter.\n");
}
```

### Ternary Conditional Operator
The ternary operator is a shorthand way of writing an `if-else` statement in a single line, allowing for concise conditional expressions.

```c
condition ? expression_if_true : expression_if_false;
```

#### Example:
```c
int a = 10;
int b = 20;
int max = (a > b) ? a : b;
```
The above code checks if `a` is greater than `b`. If true, `max` is set to `a`; otherwise, `max` is set to `b`.

### Switch-Case
The `switch` statement in C allows you to execute different blocks of code based on the value of an expression. It's often used as a more readable alternative to multiple `if-else` statements when comparing the same variable against different values.

```c
switch (expression) {
    case value1:
        // Code to be executed if expression == value1
        break;
    case value2:
        // Code to be executed if expression == value2
        break;
    default: // (optional)
        // Code to be executed if expression doesn't match any case
}
```

> **`break;`** Ends the `switch` statement. Without `break`, the program continues executing the subsequent cases (known as fall-through).

#### Example:
```c
#include <stdio.h>

int main() {
    int grade = 3;

    switch (grade) {
        case 1:
            printf("lol\n");
            break;
        case 2:
            printf("Bad.\n");
            break;
        case 3:
            printf("Meh\n");
            break;
        case 4:
            printf("Good\n");
            break;
        case 5:
            printf("Excellent!\n");
            break;
        default:
            printf("Okay\n");
    }
    return 0;
}
```

---
Next: [[Bitwise Operators]]