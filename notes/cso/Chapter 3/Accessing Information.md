An x86-64 CPU contains 16 general-purpose registers that store 64-bit values, used for both integer data and pointers.

-> The original 8086 had eight 16-bit registers, named %ax through %bp
-> IA32 extended these to 32-bit registers, labeled %eax through %ebp
-> x86-64 further expanded them to 64-bit registers, named %rax through %rbp, and introduced eight new registers, %r8 through %r15
-> The stack pointer %rsp is used to indicate end position in run time stack

![[Pasted image 20250219094716.png|500]]

Instructions can operate on data of varying sizes within the registers
-> Byte-level operations, accessing the least significant byte
-> 16-bit operations, accessing the least significant 2 bytes (word)
-> 32-bit operations, accessing the least significant 4 bytes (double word)
-> 64-bit operations, accessing the entire register (quad word)

![[Pasted image 20250219095043.png|600]]


### Operand Specifiers
Instructions utilize **operands** to specify source values for operations and destination locations to store results.

Operands can be of three types:
-> **Immediate**: Represent constant values, written with a `$` prefix
-> **Register**: Denoting the contents of a register. `Ra` represents an arbitrary register `a`, with its value indicated as `R[ra]`
-> **Memory Reference**: Accesses a memory location based on a computed address (effective address). `Mb[Addr]` denotes a reference to the b-byte value in memory starting at address `Addr`. The subscript b is often dropped for simplicity

![[Pasted image 20250219182115.png|500]]

### Data Movement Instructions
These instructions copy data between locations. The mov class is the simplest form, copying data from a source to a destination without transformation. Variants include:
->`movb`: Move byte (1 byte)
->`movw`: Move word (2 bytes)
->`movl`: Move double word (4 bytes)
->`movq`: Move quad word (8 bytes)
-> `movabsq`: Move absolute quad word

![[Pasted image 20250219182505.png|500]]

> For example, `movq %rax, %rbx` copies 8 bytes of data from register `%rax` to register `%rbx`.

When copying a smaller source value to a larger destination, extension is needed to fill the additional bits. x86-64 provides two instruction classes for this: movz (move with zero extension) and movs (move with sign extension)

-> `movz` instructions fill the remaining bytes of the destination with zeros
> Ex. If you move a 1-byte value into a 4-byte register using `movzbl`, the upper three bytes of the register will be set to zero.
![[Pasted image 20250219213302.png|670]]

-> `movs` instructions perform sign extension, where the most significant bit of the source operand is copied to the higher-order bits of the destination
> Ex. If you move a 1-byte value into a 4-byte register using `movsbl`, and the most significant bit of the byte is 1, the upper three bytes of the register will be filled with 1s.
![[Pasted image 20250219213333.png|700]]
> **NOTE**: There is no explicit `movzlq` instruction to zero-extend a 4-byte value to an 8-byte register. Instead, using `movl` with a register destination achieves this, as it zeroes the upper 4 bytes. Zero extension is supported for smaller source types, while sign extension is available for all. Additionally, the `cltq` instruction, equivalent to `movslq %eax, %rax`, sign-extends `%eax` into `%rax` with a more compact encoding.


### Data Movement Example

```c
long exchange(long *xp, long y) {
    long x = *xp;
    *xp = y;
    return x;
}
```

The function reads the value at `xp`, stores it in `x`, writes `y` to `xp`, and returns the old value.

The equivalent assembly code would be:

```nasm
exchange:
    movq (%rdi), %rax   ; Load value at xp (memory) into %rax (return value)
    movq %rsi, (%rdi)   ; Store y (from %rsi) into xp (memory)
    ret                 ; Return (value in %rax)
```

`%rdi`: Holds the pointer `xp`.
`%rsi`: Holds the argument `y`.
`%rax`: Stores the return value.

### Simple Memory Addressing Modes

**Normal:** `(R)` or `Mem[Reg[R]]` 
-> The effective address is the value stored in register `R`
-> Equivalent to pointer dereferencing in C.

**Displacement:** `D(R)` or `Mem[Reg[R] + D]`
-> The effective address is calculated by adding the constant displacement `D` to the value in register `R`.

### Complete Memory Addressing Modes

**Most General Form:** `D(Rb,Ri,S)` or `Mem[Reg[Rb]+S*Reg[Ri]+D]`
-> `D`: Constant "displacement" of 1, 2, or 4 bytes
-> `Rb`: Base register: Any of the 16 integer registers
-> `Ri`: Index register: Any, except for %rsp
-> `S`: Scaling factor: S must be 1, 2, 4, or 8

**Different Forms:**
-> `(Rb,Ri)` or `Mem[Reg[Rb]+Reg[Ri]]`
-> `D(Rb,Ri)` or `Mem[Reg[Rb]+Reg[Ri]+D`
-> `(Rb,Ri,S)` or `Mem[Reg[Rb]+S*Reg[Ri]]`

For example,
![[Pasted image 20250219221935.png|400]]

### Arithmetic and Logical Operations

Operations are divided into four groups: load effective address (`leaq`), unary, binary, and shifts.

#### `leaq`
A variant of `movq`, but instead of loading data, it computes the effective address and stores it in a register.

> `leaq <src>, <dest>`
> -> `src` is the address mode expression
> -> Set `dest` to the address denoted by expression

Used to compute addresses without actually accessing memory.

Can also be used for expressions of the form `x + k*y` (k = 1,2,4, or 8)

```nasm
leaq 7(%rdx,%rdx,4), %rax  ; Computes 5*x + 7 if %rdx contains x
```

#### Unary Operators
Instructions with one operand:
-> `incq` (`+1`)
->`decq` (`-1`)
-> `negq` (negation)
-> `notq` (bitwise complement)

```nasm
incq %rax  ; Increment %rax by 1
```

#### Binary Arithmetic Operations
Instructions with two operands
![[Pasted image 20250220121623.png|300]]

#### Signed vs Unsigned Operations
x86-64 does not differentiate between signed and unsigned arithmetic at the instruction level. The difference is in how the results are interpreted.

### Arithmetic Expression Example

```c
long arith(long x, long y, long z) {
    long t1 = x + y;
    long t2 = z + t1;
    long t3 = x + 4;
    long t4 = y * 48;
    long t5 = t3 + t4;
    long rval = t2 * t5;
    return rval;
}
```

The compiled assembly code would be:
```nasm
arith:
    leaq    (%rdi,%rsi), %rax    ; t1 = x + y
    addq    %rdx, %rax           ; t2 = z + t1
    leaq    (%rsi,%rsi,2), %rdx  ; Compute y + 2*y = 3*y
    salq    $4, %rdx             ; Multiply by 16 (3*y * 16 = 48*y)
    leaq    4(%rdi,%rdx), %rcx   ; t5 = x + 4 + 48*y
    imulq   %rcx, %rax           ; rval = t2 * t5
    ret
```
> `%rdi` → `x`
> `%rsi` → `y`
> `%rdx` → `z`, then reused for `t4`
> `%rax` → `t1`, `t2`, `rval`
> `%rcx` → `t5`

