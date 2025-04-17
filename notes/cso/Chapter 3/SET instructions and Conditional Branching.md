SET instructions allow condition codes to be stored into a register by setting a byte to either 0 or 1 depending on the condition.

The destination register’s lower byte is modified, while the upper bytes remain unchanged.

Commonly used after compare (`cmpq`) or test (`testq`) instructions to store a Boolean-like result.

-> `sete D` (Set if equal, i.e., `ZF = 1`)
-> `setne D` (Set if not equal, i.e., `ZF = 0`)
-> `setg D` (Set if greater, signed: `~(SF^OF) & ~ZF`)
-> `setge D` (Set if greater or equal, signed: `~(SF^OF)`)
-> `setl D` (Set if less, signed: `(SF^OF)`)
-> `setle D` (Set if less or equal, signed: `(SF^OF) | ZF`)
-> `seta D` (Set if above, unsigned: `~CF & ~ZF`)
-> `setb D` (Set if below, unsigned: `CF`)

![[Pasted image 20250221192049.png|500]]

Typically followed by `movzbl` to zero-extend the byte to a full register before further computations.

```nasm
cmpq   %rsi, %rdi   ; Compare y:x
setg   %al          ; Set when >
movzbl %al, %eax    ; Zero rest of %eax (and %rax)
ret
```

### `ret`

By convention, `%rax` is used to store the return value of a function.

Registers `%rbx`, `%rbp` and `%r12-r15` are callee-save registers, meaning that they are saved across function calls.

Additionally, `%rdi`, `%rsi`, `%rcx`, `%r8`, `%r9` are used to pass the first six integer or pointer parameters to called functions.


## Conditional Branches

### Jumping
![[Pasted image 20250221192702.png|500]]

```c
long absdiff(long x, long y) {
    long result;
    if(x > y) {
        result = x - y;
    } else {
        result = y-x;
    }
    return result;
}
```

To further illustrate what's happening here, we can use the `goto` statement
```c
long absdiff_j(long x, long  y) {
    long result;
    int ntest = x <= y;
    if (ntest) goto Else;
    result = x - y;
    goto Done;
Else:
    result = y - x;
Done:
    return result;
}
```

The compiled assembly code would be:
```nasm
absdiff:
   cmpq    %rsi, %rdi  ; fgffgfgfy:x
   jle     .L4
   movq    %rdi, %rax
   subq    %rsi, %rax
   ret

.L4:       ; x <= y
   movq    %rsi, %rax
   subq    %rdi, %rax
   ret
```
> `%rdi` for `x`
> `%rsi` for `y`
> `%rax` for the return value

### General Conditional Expression Translation
```c
val = (test) ? then_expr : else_expr;
```

We can do this by creating seperate code regions for then & else expressions and then executing the appropriate one.
```c
    ntest = !Test;
    if(ntest) goto Else;
    val = then_expr;
    goto Done;
Else:
    val = else_expr;
Done:
    // rest of the code
```

### Using Conditional Moves
An alternative way to implement conditional branching is through conditional transfer of *data*.

**Why use conditional moves?**
-> Branches are disruptive to control flow through pipelines
-> No control transfer needed for conditional moves

```c
result = then_expr;
eval = else_expr;
nt = !Test;
if (nt) result = eval;
return result;
```

**Example:**
```c
long absdiff(long x, long y) {
    long result;
    if (x > y)
        result = x-y;
    else
        result = y-x;
    return result;
}
```

```nasm
absdiff:
    
```

**Why not use conditional moves:**
-> Computations are expensive.
> In the case of `val = Test(x) ? Func1(x) : Func2(x)`, both values are computed.

-> Computations may be risky.
> In the case of `val = p ? *p : 0` , there may be undesirable effects as both values are computed.

-> Computations may have side effects.
>  In the case of `val = x > 0 ? x*=7 : x+=3;`, there may be side effects as both values are computed.


