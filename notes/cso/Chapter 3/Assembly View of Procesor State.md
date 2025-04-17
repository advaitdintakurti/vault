![[Pasted image 20250210133503.png|400]]

#### Program Counter (PC)
The program counter indicates the address in memory of the next instruction to be executed.
> Also called `%rip` in x86-64 (Register for Instruction Pointer)


#### Register file
The register file contains 16 named locations storing 64-bit values. These registers **can hold addresses or integer data.** 

Some registers are used to keep track of critical parts of the program state, while others are used to hold temporary data, such as the arguments and local variables of a procedure, as well as the value to be returned by a function.


#### Condition Code Registers
The Condition Code Registers store status information about the most recently performed logical/arithmetic operation. They are used for conditional branching.

#### Memory
Memory is a byte-addressable array that stores code and user data. It also stores the stack.