Bitwise operators are used to perform operations directly on the binary representations of integers. These operators manipulate individual bits within the data.

**`&` (AND)**
Compares each bit of two numbers and returns `1` if both bits are `1`; otherwise, it returns `0`.
```c
int result = 5 & 3; // 5 (0101) & 3 (0011) = 1 (0001)
```

**`|` (OR)**
Compares each bit of two numbers and returns `1` if at least one of the bits is `1`; otherwise, it returns `0`.
```c
int result = 5 | 3; // 5 (0101) | 3 (0011) = 7 (0111)
```

**`^` (XOR)**
Compares each bit of two numbers and returns `1` if the bits are different; otherwise, it returns `0`.
```c
int result = 5 ^ 3; // 5 (0101) ^ 3 (0011) = 6 (0110)
```

**`~` (NOT)**
Flips all the bits of a number, turning `1` into `0` and `0` into `1`. It is a unary operator, meaning it operates on a single operand.
```c
int result = ~5; // ~5 (0101) = -6 (in two's complement form: 1010)
```

**`<<` (Left Shift)**
Shifts the bits of the first operand to the left by the number of positions specified by the second operand. Each shift to the left effectively multiplies the number by 2.
```c
int result = 5 << 1; // 5 (0101) << 1 = 10 (1010)
```

**`>>` (Right Shift)**

Shifts the bits of the first operand to the right by the number of positions specified by the second operand. Each shift to the right effectively divides the number by 2.
```c
int result = 5 >> 1; // 5 (0101) >> 1 = 2 (0010)
```

```
arr = {arr1, arr2, arr3}
```

### Examples

#### Check parity using `XOR` operator

```c
1011 ^ 0001 = 1011
```
- If we `XOR` an even number by 1, it increments it by 1.
- If we `XOR` an odd number by 1, it decreases it by 1.

#### Check parity using `OR` operator
- If we OR an even number with 1, it increases it by 1.
- Odd numbers are unchanged.
  
You're gay btw. - ??

---
Next: [[Type Casting]]