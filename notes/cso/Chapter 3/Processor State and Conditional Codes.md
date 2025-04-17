
### Processor State
Information about the currently executing program is stored in the registers.
-> Temporary data is stored in `%rax`, `%rbx` etc. (General Purpose Registers)
-> Location of runtime stack is stored in `%rsp`
-> Location of current code control point is stored in `%rip` (Program Counter)
-> Status of recent test are stored in the (flag registers?) `CF`, `ZF`, etc.

### Condition Codes
-> **CF (Carry Flag)**: Set when an unsigned arithmetic operation results in a carry.
-> **ZF (Zero Flag)**: Set when the result of an operation is zero.
-> **SF (Sign Flag)**: Set when the result of an operation is negative (in two's complement).
-> **OF (Overflow Flag)**: Set when an operation results in signed overflow.

Condition flags are implicitly set by arithmetic operations. However, they are not set by the `leaq` instruction since it is used for address computations.

#### Compare Instruction
**`cmpq <src1>, <src2>`**
Performs `a - b` without modifying the destination but sets condition codes.
>-> CF set if unsigned `a < b`
>-> ZF set if `a == b`
>-> SF set if `(a - b) < 0`
>-> OF set if two’s complement signed overflow occurs 

#### Test Instruction
`testq <src1>, <src2>`
Performs `a & b` without modifying the destination. It is used to check whether specific bits are set.
> -> ZF set if `(a & b) == 0`
> -> SF set if the result is negative (MSB is 1)




