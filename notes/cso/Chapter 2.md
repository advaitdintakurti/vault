Modern computers store and process information represented as two-valued signals called **bits**.

#### Why use bits?
- Storing/performing computations is simple/reliable
- Easy to store with bi-stable elements
- Reliably transmitted on noisy and inaccurate wires.

### Representing Numbers

The three most important representations of numbers are:
- Unsigned
- Two's Complement
- Floating Point

Computers implement arithmetic operations, such as addition and multiplication with these different representations of numbers.

> Computer representations use a limited number of bits to encode a number, and hence some operations can **overflow** when the results are too large to be represented.
> **Ex:** `200 * 300 * 400 * 500` would evaluate to `−884,901,888` on a 32-bit system.

---

## Information Storage

Rather than accessing individual bits in memory, most computers use blocks of 8 bits, or **bytes**, as the smallest addressable unit of memory. 

A machine-level program views memory as a very large array of bytes, referred to as **virtual memory**.    Every byte of memory is identified by a unique number, known as its **address**, and the set of all possible addresses is known as the **virtual address space**.

The virtual address space is just how the memory is presented to the machine-level program and the actual implementation is quite different.

#### Hexadecimal Representation

![[hexadecimal.png]]

A **byte** consists of 8 bits, with values ranging from `00000000₂` to `11111111₂` in binary, or from `0₁₀` to `255₁₀` in decimal. Binary notation, while precise, is verbose, and decimal notation makes bit manipulation tedious. To address this, **hexadecimal (hex)** notation is commonly used.

- Hex uses 16 symbols: `0-9` and `A-F`, where `A` represents 10 and `F` represents 15 in decimal.
- A single byte in hex ranges from `00₁₆` to `FF₁₆`.

> In the C programming language, numeric constants starting with `0x` or `0X` are interpreted as hexadecimal. For instance:
> - `0xFA1D37B`, `0xfa1d37b`, or `0xFa1D37b` all represent the same value.
> - Both uppercase and lowercase for `A-F` are valid.


### Data Sizes

Every computer has a **word size**, indicating the nominal size of pointer data. This word size determines the maximum size of the **virtual address space**, which ranges from 0 to 2<sup>w</sup> - 1 for a w-bit word size, allowing access to up to 2<sup>w</sup> bytes of memory.

> **32-bit word size**: Virtual address space is limited to **4 GB** (4×10<sup>9</sup> bytes).
> **64-bit word size**: Expands the address space to **16 exabytes** (1.84×10<sup>19</sup> bytes).
> 
> Modern 64-bit systems maintain **backward compatibility** to run 32-bit programs. For example:
> - A program compiled with `gcc -m32` runs on both 32-bit and 64-bit machines.
> - A program compiled with `gcc -m64` runs only on 64-bit machines.

#### Data Types and Sizes in C

C supports multiple data formats for both integers and floating-point numbers, with typical sizes differing between 32-bit and 64-bit programs:

**Integer types**:
- `char`: 1 byte (can store a character or an integer).
- `short`, `int`, and `long`: Provide different ranges.
- `int` is usually 4 bytes, even on 64-bit systems.
- `long` is 4 bytes for 32-bit programs but 8 bytes for 64-bit programs.
   
**Floating-point types**:
- `float` (single precision): 4 bytes.
- `double` (double precision): 8 bytes.

**Pointer types**: Use the program's full word size (4 bytes for 32-bit, 8 bytes for 64-bit).

#### Fixed-Size Data Types

To avoid inconsistencies due to compiler or machine settings, **ISO C99** introduced fixed-size types:
- `int32_t`: Exactly 4 bytes.
- `int64_t`: Exactly 8 bytes.  
These ensure precise control over data representation.

#### Signed and Unsigned Types
- Most integer types are **signed** by default, representing negative, zero, and positive values.
- Adding the `unsigned` keyword (e.g., `unsigned int`) restricts values to non-negative numbers.
- **`char`**: The default signedness of `char` is not guaranteed by the C standard. To enforce signed or unsigned behavior, explicitly use `signed char` or `unsigned char`.

### Addressing and Byte Ordering

When working with multi-byte objects in memory, two conventions must be established:

**Address Assignment**: The object's address is defined as the smallest address among the bytes it occupies.
- **Example**: If an `int` variable `x` has address `0x100` and occupies 4 bytes (32-bit representation), its bytes are stored in locations `0x100`, `0x101`, `0x102`, and `0x103`.
 
**Byte Ordering**: The arrangement of bytes for an object in memory.
- **Little-Endian**: Stores the least significant byte (LSB) first, i.e., at the lowest memory address.
- **Big-Endian**: Stores the most significant byte (MSB) first, i.e., at the lowest memory address.

For an `int x` at address `0x100` with value `0x01234567`:
![[endian.png|600]]
> The terms "little-endian" and "big-endian" originate from _Gulliver's Travels_ by Jonathan Swift, where two factions argued about which end of an egg to crack open. Similarly, the choice of byte ordering is arbitrary but must be consistent.

> Communication between little-endian and big-endian machines can lead to incorrect data interpretation. To address this, networking protocols enforce a **network standard** for byte ordering. Sending and receiving machines convert data accordingly.

#### Byte Representation in C

```c
#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}
```

**`show_bytes`:**
- Prints the byte-level representation of an object.
- Uses the `unsigned char *` type to interpret memory as a sequence of bytes.
- The `%.2x` format specifier prints each byte in 2-digit hexadecimal.

**`show_int`, `show_float`, `show_pointer`**:
- Demonstrates how to display the byte representation of integers, floats, and pointers by passing their addresses to `show_bytes`.

> Using `sizeof` ensures compatibility across different machine types by dynamically determining the size of the object.

```c
void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;

    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}
```

![[byte-representation.png|600]]

#### Representing Strings

A string in C is encoded by an array of characters terminated by the null (having
value 0) character. Each character is represented by some standard encoding, with
the most common being the ASCII character code.

#### Representing Code

```c
int sum(int x, int y) {
    return x + y;
}
```

Corresponding machine code:
![[machine-code-i-guess.png|800]]

Instruction codings are generally different between different machine/OS types (so the binaries are not portable.) 

From the perspective of the machine, a program is simply a sequence of bytes. The machine has no information about the original source program, except perhaps some auxiliary tables maintained to aid in debugging. 

---

## Boolean Algebra

> Developed by George Boole in 19th Century

Boole observed that by encoding logic values true and false as binary values 1 and 0, he could formulate an algebra that captures the basic principles of logical reasoning

![[boolean-algebra.png]]
We can extend the four Boolean operations to also operate on bit vectors (strings of zeros and ones of some fixed length w.) We define the operations over bit vectors according to their applications to the matching elements of the arguments

Let a and b denote the bit vectors `[a_w−1, a_w−2, . . . , a_0]` and `[b_w−1, b_w−2, . . . , b_0]`, respectively. We define a & b to also be a bit vector of length w, where the i<sup>th</sup> element equals (a<sub>i</sub> & b<sub>i</sub>), for 0 ≤ i < w. The operations `|`, `^`, and `~` are extended to bit vectors in a similar fashion.

![[boolean-algebra-2.png|800]]

### Representing and Manipulating Sets

We can encode any subset `{0, …, w–1}` with a bit vector `[a_w-1, a_w-2, …, a_0]`, where a<sub>i</sub> = 1 if and only if i ∈ A.

#### Operations:
- Intersection (Using `&`)
- Union (Using `|`)
- Symmetric Difference (Using `^`)
- Complement (Using `~`)


### Bit-Level Operations in C

C supports bitwise boolean operations: `&` (AND), `|` (OR), `~` (NOT), `^` (XOR)

These operations apply to any “integral” data type: `long`, `int`, `short`, `char`, `unsigned`. Arguments are viewed as bit vectors.

![[boolean-algebra-3.png|800]]


#### Bit-Level Masking Operations

Masking is a technique used to isolate specific bits in a word. A common example is the mask `0xFF`, which selects the least significant byte (LSB). Applying `x & 0xFF` extracts the LSB while setting all other bytes to zero.

For example, if `x = 0x89ABCDEF`, then `x & 0xFF` results in `0x000000EF`.

To create a mask with all bits set to `1`, the expression `~0` is used. This is equivalent to `0xFFFFFFFF` in a 32-bit integer but remains more portable across different data sizes.


### Logical Operations in C

C provides logical operators `||` (or), `&&` (and), and `!` (not).

Logical operations treat any nonzero argument as representing true and argument 0 as representing false. They return either 1 or 0, indicating a result of either true or false, respectively.

Logical operators do not evaluate their second argument if the result of the expression can be determined by evaluating the first argument.
> Ex. `a && 5/a` will never cause division by zero.


### Shift Operations

C also provides a set of shift operations for shifting bit patterns to the left and to the right.

**Left Shift:** `x << y`
- Shift bit-vector x left y positions
- Throw away extra bits on left
- Fill with 0’s on right

**Right Shift:** `x >> y`
- Shift bit-vector x right y positions
- Throw away extra bits on right
- Logical shift: Fill with 0’s on left
- Arithmetic shift: Replicate the most significant bit on the left

![[shift-operations.png|500]]

The C standards do not precisely define which type of right shift should be used with signed numbers either arithmetic or logical shifts may be used. In practice, however, almost all compiler/machine combinations use arithmetic right shifts for signed data, and many programmers assume this to be the case. For unsigned data, on the other hand, right shifts must be logical.

Undefined behavior may occur when shift amount < 0 or ≥ word size.

On many machines, the shift instructions consider only the lower log2 w bits of the shift amount when shifting a w-bit value, and so the shift amount is computed as `k mod w`.

---

# Integer Representations

C supports a variety of integral data types—ones that represent finite ranges of integers.

![[data-types-32.png|600]]
![[data-types-64.png|600]]

#### Unsigned Encodings

Nonnegative numbers are encoded based on binary notation. We write a bit vector as either x, to denote the entire vector, or as `[x_w−1, x_w−2, . . . , x_0]` to denote the individual bits within the vector. 

![[def-unsigned.png|700]]


#### Two's Complement Encoding

Represents signed integers. This is done by interpreting the most significant bit of the word to have
negative weight.

![[def-twoscomp.png|700]]

The most significant bit `x_w-1` is the sign bit, with a weight of `-2^(w-1)`
> Regular bits (`x_i`) have a weight of  `2^i` btw