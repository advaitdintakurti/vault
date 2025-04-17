### Variables

Variables store data that can change during program execution. They are defined by specifying a data type followed by a variable name.
```c
int age = 17;
float height = 5.9f;
char initial = "A";
```

#### Rules:
- Variable names must start with a letter or underscore.
- They can contain letters, digits, and underscores.
- They are case-sensitive.

### Constants

Constants store data that remains unchanged throughout the program. They can be defined using `const` or `#define`.
```c
const int MAX_AGE = 100;
#define PI 3.14159
```

**`const`**: Prevents the variable's value from being modified
**`define`**: A preprocessor directive that creates a constant value, substituted directly into the code during preprocessing.

### Compound Assignment Operators

```c
x += 5;  // Equivalent to x = x + 5;
x -= 3;  // Equivalent to x = x - 3;
x *= 2;  // Equivalent to x = x * 2;
x /= 2;  // Equivalent to x = x / 2;
x %= 4;  // Equivalent to x = x % 4;
```

### Swapping Variables

```c
int x = 10;
int y = 20;
```

#### M1: Swapping Variables
```c
z = x; // z = 10  
x = y; // x = 20, y = 20  
y = z; // y = 10
```

#### M2: Algebra?
```c
x = x + y
y = x - y
x = x - y
```

#### M3: Whatever this is
```c
x = x+y-(y=x);
```
`(y=x)` is evaluated first as it is in brackets

#### XOR
```c
x = x^y
y = x^y
x = x^y
```

---
Next: [[Data Types]]