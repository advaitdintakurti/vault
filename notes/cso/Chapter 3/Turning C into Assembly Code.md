`mstore.c`
```c
long mult2(long, long);

void multstore(long x, long y, long *dest) {
    long t = mult2(x, y);
    *dest = t;
}
```

To obtain assembly code:
```
linux> gcc -Og -S mstore.c
```
> `-Og`: For basic optimisations
> `-S`: To see assembly code

`gcc` runs the compiler, which generates assembly file `mstore.s`, and then stops without moving on to the assembler.

>  Can get very different results for `mstore.c` on different machines due to different versions of gcc and different compiler settings.

`mstore.s`
```nasm
	.file	"mstore.c"
	.text
	.globl	multstore
	.type	multstore, @function
multstore:
.LFB0:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdx, %rbx
	call	mult2
	movq	%rax, (%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	multstore, .-multstore
	.ident	"GCC: (GNU) 14.2.1 20241116"
	.section	.note.GNU-stack,"",@progbits
```

All of the lines beginning with `.` are directives to guide the assembler and linker. 

`mstore.s` (The relevant part)
```nasm
; void multstore(long x, long y, long *dest)
; x in %rdi, y in %rsi, dest in %rdx
multstore:
	pushq	%rbx              ; Save %rbx
	movq	%rdx, %rbx        ; Copy dest to %rbx
	call	mult2             ; Call mult2(x,y)
	movq	%rax, (%rbx)      ; Store result at *dest
	popq	%rbx              ; Restoer %rbx
	ret                       ; Return
```

### Assembly Characteristics

`mstore.s` contains various declarations. Here, each indented line corresponds to a single machine instruction. All information about local variable names/data types has been stripped away.

#### Data Types
**Integer Data:** `char` (1 byte), `short` (2 bytes), `int` (4 bytes), `long`, `char*` (8 bytes)
**Floating Point Data:** `float` (4 bytes), `double` (8 bytes), `long double` (10 bytes)
**Code:** Byte sequences encoding series of instructions

![[Pasted image 20250210142511.png|600]]

#### Operations
Operations in assembly either:
- Perform arithmetic functions on register or memory data
- Transfer data between memory and register
- Transfer control (flow)


### Object Code

Can be obtained by `gcc -Og -c mstore.c` (both compile and assemble)

`mstore.o`
```
0x0400595: 
   0x53
   0x48
   0x89
   0xd3
   0xe8
   0x00
   0x00
   0x00
   0x00
   0x48
   0x89
   0x03
   0x5b
   0xc3
```

#### Assembler
The assembler translates `.s` files into `.o`.  This translation involves converting assembly instructions into their binary representations. It generates a nearly-complete image of executable code.
However, there are some missing linkages between code in different files.

#### Linker
The linker resolves references between different files. It combines object code files with each other and with static run-time libraries (eg. code for `malloc`, `printf`)
The linker fills in the addresses of global values and matches function calls with the locations of the executable code for those functions.

> Some libraries are **dynamically linked**, with linking occurring when the program begins.

### Machine Instruction Example

**C Code:**
Store value `t` where designated by `dest`
```c
*dest = t;
```

**Assembly:**
Move 8-byte value to memory
```nasm
movq %rax, (%rbx)
```

**Object Code:**
3-byte instruction stores at address `0x40059e`
```
0x40059e:  48 89 03
```

### Disassembling Object Code

**Disassemblers** are tools that generate a format similar to assembly code from machine code. They are a useful tool for examining object code.

Disassemblers produce an approximate rendition of assembly code purely on byte sequences in the machine-code file and do not require access to the source or assembly-code versions of the program.

The disassembly output includes:
-> The address of each instruction
-> The byte values of the machine code
-> The equivalent assembly language instruction

`linux> objdump -d mstore.o`
> can be run on either object file or complete executable
```
mstore.o:	file format elf64-x86-64

Disassembly of section .text:

0000000000000000 <multstore>:
       0: 53                           	pushq	%rbx
       1: 48 89 d3                     	movq	%rdx, %rbx
       4: e8 00 00 00 00               	callq	0x9 <multstore+0x9>
       9: 48 89 03                     	movq	%rax, (%rbx)
       c: 5b                           	popq	%rbx
       d: c3                           	retq
```

`x86-64` instructions can range in length from 1 to 15 bytes. The encoding is such that commonly used instructions require fewer bytes.