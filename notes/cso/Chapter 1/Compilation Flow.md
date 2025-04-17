In order to run hello.c on the system, the individual C statements must be translated into a sequence of low-level machine-language instructions.

These instructions are then packaged in a form called an executable object program and stored as a binary disk file. Object programs are also referred to as executable object files.

![[compilation-system.png]]
The `gcc` compiler reads the source file `hello.c` and translates it into an executable object file `hello`.

#### Preprocessor (`cpp`)
Modifies the original C program according to directives that begin with the ‘`#`’ character.

For example, the`#include <stdio.h>` command of `hello.c` tells the preprocessor to read the contents of `stdio.h` and insert it directly into the program text. The resulting C program has a `.i` suffix.

#### Compiler (`cc1`)
The compiler (`cc1`) translates the text file `hello.i` into the text file `hello.s`, which contains an assembly-language program. This program includes the following definition of function main:
![[hello-world-asm.png|300]]

#### Assembler (`as`)
The assembler (`as`) translates `hello.s` into machine-language instructions, packages them in a form known as a *relocatable object program*, and stores the result in the object file `hello.o`, which is a binary file.

#### Linker (`ld`)
Our `hello.c` program calls the `printf` function, which is part of the standard C library. The printf function resides in a separate precompiled object file called `printf.o`, which must be merged with `hello.o`. The linker (`ld`) handles this merging. The result is the hello file, which is an executable object file that is ready to be executed.

#### Understanding compilation systems helps with:

- Writing code that is more optimized.
- Understanding link-time errors which are hard to catch.
- Avoiding security holes.

### Execution:
The C program `hello.c`  has been converted to an executable `hello`  by the compilation process. To run the executable, we type its name on a **shell.**

```
> ./hello
hello, world
```

The shell is a command-line interpreter that prints a prompt, waits for you to type a command, and then performs the command.

In this case, the shell loads and runs the `hello` program and then waits for it to terminate.