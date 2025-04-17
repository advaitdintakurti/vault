Operators in C are symbols that perform operations on variables and values.

### **Arithmetic Operators**

These operators perform mathematical operations.

- **`+` (Addition)**: Adds two operands.
    - **Example**: `c = a + b;`
- **`-` (Subtraction)**: Subtracts the second operand from the first.
    - **Example**: `c = a - b;`
- **`*` (Multiplication)**: Multiplies two operands.
    - **Example**: `c = a * b;`
- **`/` (Division)**: Divides the first operand by the second.
    - **Example**: `c = a / b;`
- **`%` (Modulus)**: Returns the remainder of division.
    - **Example**: `c = a % b;` (Useful for determining if a number is even or odd)

### **Relational Operators**

These operators compare two values and return a boolean result (true/false).

- **`==` (Equal to)**: Returns true if both operands are equal.
- **`!=` (Not equal to)**: Returns true if operands are not equal.
- **`>` (Greater than)**: Returns true if the left operand is greater than the right.
- **`<` (Less than)**: Returns true if the left operand is less than the right.
- **`>=` (Greater than or equal to)**: Returns true if the left operand is greater than or equal to the right.
- **`<=` (Less than or equal to)**: Returns true if the left operand is less than or equal to the right.

### **Increment and Decrement Operators**

These operators increase or decrease a variable's value by 1.

- **`++` (Increment)**: Increases an integer's value by 1.
    - **Example**: `a++;` or `++a;`
- **`--` (Decrement)**: Decreases an integer's value by 1.
    - **Example**: `a--;` or `--a;`

**Order of Operation**:

**Prefix**: The operation (increment or decrement) is performed before the variable’s value is used in the expression. Ex. `++a` , `--a`
```c
int a = 5;
int b = ++a; // a is incremented to 6, then b is assigned 6
```

**Postfix**: The operation is performed after the variable’s value is used in the expression. Ex. `a++`, `a--`
```c
int a = 5;
int b = a++; // b is assigned 5, then a is incremented to 6
```

### Preference Order (highest to lowest)

| Category         | Operator                         | Associativity     |
| ---------------- | -------------------------------- | ----------------- |
| Grouping/Postfix | `() [] -> . a++ a--`             | Left to right     |
| Unary            | `+ - ! ~ ++a --a (type)* sizeof` | **Right to left** |
| Multiplicative   | `* / %`                          | Left to right     |
| Additive         | `+ -`                            | Left to right     |
| Shift            | `<< >>`                          | Left to right     |
| Relational       | `< <= > >=`                      | Left to right     |
| Equality         | `== !=`                          | Left to right     |
| Bitwise AND      | `&`                              | Left to right     |
| Bitwise XOR      | `^`                              | Left to right     |
| Bitwise OR       | \|                               | Left to right     |
| Logical AND      | `&&`                             | Left to right     |
| Logical OR       | \|\|                             | Left to right     |
| Conditional      | `?:`                             | **Right to left** |
| Assignment       | All assignment operators         | **Right to left** |
| Comma            | `,`                              | Left to right     |

---
Next: [[Assignment]]