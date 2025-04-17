Data types in C define the type and size of data that variables can hold. Understanding these types is fundamental for writing efficient and error-free programs.

### Basic Data Types

1. **`int`**:
    - Stores integers (whole numbers).
    - Typically 4 bytes (varies by system).
    - Example: `int age = 25;`
2. **`float`**:
    - Stores floating-point numbers (single precision).
    - Typically 4 bytes.
    - Example: `float pi = 3.14f;`
3. **`double`**:
    - Stores double-precision floating-point numbers.
    - Typically 8 bytes.
    - Example: `double largePi = 3.14159265358979;`
4. **`char`**:
    - Stores a single character.
    - Typically 1 byte.
    - Example: `char initial = 'A';`

### Derived Data Types

1. **`arrays`**:
    - Collection of elements of the same type.
    - Example: `int numbers[5] = {1, 2, 3, 4, 5};`
    
2. **`pointers`**:
    - Stores memory addresses.
    - Example: `int *ptr = &age;`
    
3. **`struct`**:
    - Custom data type that groups variables of different types.
```c
struct Person { char name[50]; int age; };
```
        
4. **`union`**:
- Similar to `struct`, but members share the same memory location. 
```c
union Data {
    int intValue;
    float floatValue;
};
```


### Enumerated Data Type
Defines a set of named integer constants
```c
enum Weekday {Sunday, Monday, Tuesday};
enum Weekday today = Sunday;
```

### Type Modifiers

1. **`short`**, **`long`**:
    - Alters the size of `int` or `double`.
    - Example: `short int age;`, `long double distance;`
    
2. **`signed`**, **`unsigned`**:
    - Specifies whether a variable can hold negative values.
    - Example: `unsigned int count;`

### Size and Range of Basic Types

- **`char`**: 1 byte (8 bits)
    - Signed: `-2^7 to 2^7 - 1` (`-128 to 127`)
    - Unsigned: `0 to 2^8 - 1` (`0 to 255`)
    
- **`int`**: 4 bytes (32 bits)
    - Signed: `-2^31 to 2^31 - 1` (`-2,147,483,648 to 2,147,483,647`)
    - Unsigned: `0 to 2^32 - 1` (`0 to 4,294,967,295`)
    
- **`float`**: 4 bytes (32 bits)
    - Range: `~2^-126 to 2^128`, ~24-bit precision
    
- **`double`**: 8 bytes (64 bits)
    - Range: `~2^-1022 to 2^1024`, ~53-bit precision
    
- **`short`**: 2 bytes (16 bits)
    - Signed: `-2^15 to 2^15 - 1` (`-32,768 to 32,767`)
    - Unsigned: `0 to 2^16 - 1` (`0 to 65,535`)
    
- **`long` / `long long`**: 8 bytes (64 bits)
    - Signed: `-2^63 to 2^63 - 1` (`-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807`)
    - Unsigned: `0 to 2^64 - 1` (`0 to 18,446,744,073,709,551,615`)#

---
Next: [[printf()]]
