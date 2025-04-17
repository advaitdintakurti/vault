
Type casting is the method used to change one data type to another.

> Hierarchy of data types is based on size.
> `int` -> `unsigned int` -> `long` -> `unsigned long` -> `long long` -> `unsigned long long` -> `float` -> `double` -> `long double`

## Implicit Type Casting
Happens implicitly, without being specified in the program
```c
short a = 10;
int b;
b = a;
```

## Explicit Type Casting
Happens when specified in the program like so: `a = (<type>)a`
```c
int a = 15; // a = 15
a = (float)a; // a is now a float

int b = 12; // b and c are integers
int c = 5;

float div;
div = (float)b/c; // b is converted to float before division
```

## Specialized Type Casting Functions
- `atof()`: `String` -> `float`
- `atoi()`: `String` -> `int`
- `atbol()`: `String` -> `long`
- `ltoa()`: `long` -> `String`
- `itoba()`: `int` -> `String`
---
 Next: [[Arrays]]